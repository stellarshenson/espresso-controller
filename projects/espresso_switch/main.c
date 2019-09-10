/*
 * 
 * Espresso controller accessory where On/Of functions
 * by toggling monostable switch and looks at the SENSE
 * pin to find if espresso machine is on 
 * 
 * This accessory uses the modified wifi-config library
 * that has the homekit id generated from the chipid and
 * starts an AP mode with a HTTP server upon start when 
 * wifi config was found.
 *
 * After successful connection accessory shuts down AP.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>
#include <string.h> 

#include <serial-cmdline.h>

#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <wifi_config.h>
#include <button.h>
#include <espressif/esp_system.h>

#define GPIO_ESPRESSO_TOGGLE	2
#define GPIO_STATUS_LED		2
#define GPIO_ESPRESSO_SENSE	4
#define ESPRESSO_SENSE_DELAY	1000

//pairing password to display, this will be embedded in the AP homepage
#define CUSTOM_SECTION "<p><b>Homekit Accessory ID:</b><br> %s </p>"
#define INITIAL_ACCESSORY_PASSWORD "000-00-000"

#define HOMEKIT_CUSTOM_UUID(value) (value "-03a1-4971-92bf-af2b7d833922")
//#define HOMEKIT_SERVICE_CUSTOM_SETUP HOMEKIT_CUSTOM_UUID("F00000FF")
#define HOMEKIT_CHARACTERISTIC_CUSTOM_SHOW_SETUP HOMEKIT_CUSTOM_UUID("00000001")
#define HOMEKIT_DECLARE_CHARACTERISTIC_CUSTOM_SHOW_SETUP(_value, ...) \
    .type = HOMEKIT_CHARACTERISTIC_CUSTOM_SHOW_SETUP, \
    .description = "Show Setup", \
    .format = homekit_format_bool, \
    .permissions = homekit_permissions_paired_read \
    | homekit_permissions_paired_write \
    | homekit_permissions_notify, \
    .value = HOMEKIT_BOOL_(_value), \
    ##__VA_ARGS__

//prototypes
void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context);
void espresso_sense_task();
void espresso_toggle(bool on);
void status_led_write(bool on);
void accessory_identify_task(void *_args);
void accessory_identify_callback(homekit_value_t _value);
void show_setup_callback();
void serial_read_task();
void on_command(char* cmd);

/*
 * declared characteristics:
 * espresson_on - controls espresso power
 * show_setup - controls whether custom setup visibility
 * */
homekit_characteristic_t espresso_on = HOMEKIT_CHARACTERISTIC_(ON, false, .callback=HOMEKIT_CHARACTERISTIC_CALLBACK(espresso_on_callback));
homekit_characteristic_t show_setup = HOMEKIT_CHARACTERISTIC_(CUSTOM_SHOW_SETUP, true, .callback=HOMEKIT_CHARACTERISTIC_CALLBACK(show_setup_callback));
//homekit_characteristic_t wifi_reset = HOMEKIT_CHARACTERISTIC_(CUSTOM_WIFI_RESET, false, .id=131, .callback=HOMEKIT_CHARACTERISTIC_CALLBACK(change_settings_callback));

// declare accessories / services and characteristics
// those are furhter initialised with homekit_server_init after wifi is configured
homekit_accessory_t *accessories[] = {
    //accessories
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]){
	//servces - information
	HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]){
	    //characteristics
	    HOMEKIT_CHARACTERISTIC(NAME, "Espresso Switch"),
	    HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Stellars"),
	    HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "001"),
	    HOMEKIT_CHARACTERISTIC(MODEL, "Momentary Switch"),
	    HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.3"),
	    HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify_callback),
	    NULL
	}),
	//services - switch
	HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
	    HOMEKIT_CHARACTERISTIC(NAME, "Espresso Switch"),
	    &espresso_on,
	    &show_setup,
	    NULL
	}),
	NULL
    }),
    NULL
};

//homekit server configuration - initial password and the list of declared accessories 
homekit_server_config_t config = {
    .accessories = accessories,
    .password = INITIAL_ACCESSORY_PASSWORD
};

//sense value set by the sense task
volatile homekit_value_t espresso_sense_on = { .bool_value = false }; //changed by internal sense task
volatile homekit_value_t simulate_on = { .bool_value = false }; //changed by commands
volatile bool simulation_enabled = false;  //when true, status is read only from commands until next reboot


/**
 * espresso callback function to receive value and enable the toggle
 * when callback was initated by the sense task - no action is taken
 * */
void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context) {
    if(espresso_sense_on.bool_value != on.bool_value) { 
	espresso_toggle(on.bool_value);
    } else {
	espresso_on.value.bool_value = on.bool_value;
	status_led_write(on.bool_value);
    };
}

/**
 * toggle the switch 
 * espresso has only momentary switch, it needs to be toggled on-and-off
 * and the internal espresso circuits will be energised. When state is off,
 * the the on-and-off toggle will turn espresso machine off
 * */
void espresso_toggle(bool on) {
    printf("espresso toggle %u, current state is %u\n", on, espresso_sense_on.bool_value);
    gpio_write(GPIO_ESPRESSO_TOGGLE, 1);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    gpio_write(GPIO_ESPRESSO_TOGGLE, 0);

    //set value
    espresso_on.value.bool_value = on;
    status_led_write(on);
}

/**
 * LED status light
 * */
void status_led_write(bool on) {
    gpio_write(GPIO_STATUS_LED, on ? 0 : 1);
}

/**
 * initialises the espresso state sense and prepare the toggle
 * this function launches the perpetual task to check the status of
 * of the espresso circuit and notifiy homekit on the status change
 * */
void espresso_init() {
    //enable ESPRESSO_TOGGLE pin for OUTPUT and ESPRESSO_SENSE for INPUT
    gpio_enable(GPIO_ESPRESSO_TOGGLE, GPIO_OUTPUT);
    gpio_enable(GPIO_ESPRESSO_SENSE, GPIO_INPUT);
    gpio_set_pullup(GPIO_ESPRESSO_TOGGLE, true, true);
    gpio_set_pullup(GPIO_ESPRESSO_SENSE, true, true);
    status_led_write(false);
    
    //enable sense task
    xTaskCreate(espresso_sense_task, "Espresso Sense", 512, NULL, 3, NULL);
}


/**
 * monitor the status of espresso power
 * run this in a loop, find if the sense pin changed state
 * */
void espresso_sense_task() {

    //keep monitoring by going idle for a predefined time and then sense again.
    //when status of the espresso changed - notify homekit
    while(1) {
	vTaskDelay(ESPRESSO_SENSE_DELAY / portTICK_PERIOD_MS);
	
	//by default read status from GPIO_ESPRESSO_SENSE. Otherwise read from simulation
	if(! simulation_enabled) espresso_sense_on.bool_value = gpio_read(GPIO_ESPRESSO_SENSE);
	else espresso_sense_on.bool_value = simulate_on.bool_value; //read simulation value

	//when internal state different from homekit state - notify
	if( espresso_sense_on.bool_value != espresso_on.value.bool_value ) homekit_characteristic_notify(&espresso_on, espresso_sense_on);
    }

    vTaskDelete(NULL);
}

/**
 * identify accessort
 * */
void accessory_identify_callback(homekit_value_t _value) {
    printf("Accessory identify\n");
    xTaskCreate(accessory_identify_task, "Accessory identify", 128, NULL, 2, NULL);
}

/**
 * show setup in the configuration app (eve)
 * */
void show_setup_callback() {
   //save_settings();
}



/**
 * task run to identify the accessory
 * */
void accessory_identify_task(void *_args) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            status_led_write(true);
            vTaskDelay(100 / portTICK_PERIOD_MS);
             status_led_write(false);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        vTaskDelay(250 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}


/**
 * process commands
 * */
void on_command(char* cmd) {
    if(!strcmp(cmd, "reset")) {
	printf("resetting system\n");
	wifi_config_reset();
	vTaskDelay(500 / portTICK_PERIOD_MS); 	
	homekit_server_reset();
	vTaskDelay(500 / portTICK_PERIOD_MS); 	
	sdk_system_restart();
    } else if( !strcmp(cmd, "reset_wifi") ) {
	printf("resetting wifi settings\n");
	wifi_config_reset();
	sdk_system_restart();
    } else if( !strcmp(cmd, "reset_accessory") ) {
	printf("resetting accessory pairing and settings\n");
	homekit_server_reset();
	sdk_system_restart();
    } else if( !strcmp(cmd, "reboot") ) {
	printf("rebooting\n");
	sdk_system_restart();
    } else if( !strcmp(cmd, "simulate_on") ) {
	printf("Simulating espresso internal on\n");
	simulation_enabled = true;
	simulate_on.bool_value = true;
    } else if( !strcmp(cmd, "simulate_off") ) {
	printf("Simulating espresso internal off\n");
	simulation_enabled = true;
	simulate_on.bool_value = false;
    } else if( !strcmp(cmd, "simulation_disable") ) {
	printf("Disabling simulation\n");
	simulation_enabled = false;
    } else if( !strcmp(cmd, "status") ) {
	printf("Espresso machine status: %u\n", espresso_sense_on.bool_value);
    } else if( !strcmp(cmd, "help") ) {
	printf("Available commands:\n\
	reboot - reboots the device, no changes to the settings\n\
	reset - resets the device settings to factory\n\
	reset_accessory - resets pairing and accessory information and restarts homekit server\n\
	reset_wifi - resets wifi ssid and password and reboots\n\
	switch_on - turns the espresso machine on\n\
	switch_off - turns the espresso machine off\n\
	simulate_on - simulates espresso power state on\n\
	simulate_off - simulates espresso power state off\n\
	simulation_disable - disable simulation\n\
	status - returns the status of the espresso power circuit\n");
    }
}



/**
 * called when wifi configuration was completed
 * this function starts the homekit server
 * */
void on_wifi_ready() {
    printf("CUSTOM_SHOW_SETUP\n");
    homekit_server_init(&config);
}


/**
 * generates accessory password from the chip_id, turns 32 bit chipID into 4-bit chunks and gets modulo 9 from each
 * and generates the custom section to be displayed with the wifi_config AP server
 * */
void accessory_password_init() {
    uint32_t chipid = sdk_system_get_chip_id();
    uint8_t accessory_id_digits[] = { chipid >> 0 & 0xf % 10,  chipid >> 4 & 0xf % 10, chipid >> 10 & 0xf % 10, 
    	chipid >> 12 & 0xf % 10, chipid >> 16 & 0xf % 10, chipid >> 20 & 0xf % 10, chipid >> 24 & 0xf % 10, chipid >> 28 & 0xf % 10 }; 
    config.password = (char*) malloc( 11 * sizeof(char));
    char *buffer = (char*) malloc(strlen(config.password) + strlen(CUSTOM_SECTION)); 

    //write accessory password 
    snprintf(config.password, 11, "%u%u%u-%u%u-%u%u%u", accessory_id_digits[0], accessory_id_digits[1], accessory_id_digits[2], 
    	                               accessory_id_digits[3], accessory_id_digits[4], accessory_id_digits[5], accessory_id_digits[6], accessory_id_digits[7]);

    printf(">>> accessory password: %s\n", config.password);

    //write custom section with the password
    snprintf(buffer, strlen(config.password) + strlen(CUSTOM_SECTION) + 1, CUSTOM_SECTION, config.password);
    
    printf(">>> custom section: %s\n", buffer);

    //set custom section. This is used in the wifi-config library
    wifi_config_custom_section_set(buffer);
}


void user_init(void) {
    uart_set_baud(0, 74880); //using the same baud rate as boot loader (to not switch monitor)
    serial_cmdline_init( on_command ); //initialise command listener with on_command callback
    accessory_password_init();
    wifi_config_init("stellars", NULL, on_wifi_ready);
    espresso_init();
}
