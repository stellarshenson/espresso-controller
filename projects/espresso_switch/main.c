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
#include <sysparam.h>

#include <serial-cmdline.h>
#include <led_status.h>

#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <wifi_config.h>
#include <adv_button.h>
#include <espressif/esp_system.h>
#include <espressif/esp_common.h>
#include <esp/hwrand.h>

/* the following is for fetching the time over ntp protocol */
#include <sntp.h>
#include <time.h>

#ifndef PROTO_UUID
#define PROTO_UUID "-03a1-4971-92bf-af2b7d833922"
#endif

#ifndef UUID
#define UUID "01010101" PROTO_UUID
#endif

#define INFO(message, ...) printf(">>> " message "\n", ##__VA_ARGS__);
#define ERROR(message, ...) printf("!!! " message "\n", ##__VA_ARGS__);

#define GPIO_ESPRESSO_RELAY    14
#define GPIO_STATUS_LED         2
#define GPIO_ESPRESSO_SENSE     12
#define GPIO_BUTTON             4
#define ESPRESSO_SENSE_DELAY    1000
#define ESPRESSO_TOGGLE_TIME    500
#define SNTP_SYNC_PERIOD	5*60000	
#define SNTP_SERVERS		"0.pool.ntp.org", "1.pool.ntp.org", "2.pool.ntp.org", "3.pool.ntp.org"

#define DEFAULT_SWITCH_MODE	switch_mode_momentary

#define SYSPARAM_SWITCH_MODE		"switch_mode"
#define SYSPARAM_HOMEKIT_PASSWORD	"homekit_password"
#define SYSPARAM_BOOTSTRAPPED		"device_bootstrapped"


//pairing password to display, this will be embedded in the AP homepage
#define CUSTOM_HTML "<p><b>Espresso Switch Accessory </b><br> %s </p>"
#define INITIAL_ACCESSORY_PASSWORD "111-11-111"

#define HOMEKIT_CUSTOM_UUID(value) (value PROTO_UUID)
#define HOMEKIT_SERVICE_CUSTOM_SETUP HOMEKIT_CUSTOM_UUID("F00000FF")
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
void espresso_toggle(bool _on);
void espresso_cycle();
void status_led_write(bool on);
void accessory_identify_task(void *_args);
void accessory_identify_callback(homekit_value_t _value);
void led_identify(homekit_value_t _value);
void show_setup_callback();
void serial_read_task();
void on_command(char* cmd);
void reset_settings();
void save_settings();
void espresso_status();

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
homekit_server_config_t homekit_config = {
    .accessories = accessories,
    .password = ""
};

//mode of operation
typedef enum {
    switch_mode_momentary = 0,
    switch_mode_toggle = 1
} switch_mode_t;


//sense value set by the sense task
volatile homekit_value_t espresso_sense_on = { .bool_value = false }; //changed by internal sense task
volatile homekit_value_t simulate_on = { .bool_value = false }; //changed by commands
volatile bool simulation_enabled = false;  //when true, status is read only from commands until next reboot
volatile bool led_status = false; //led status, need for reporting status
volatile int8_t switch_mode = (int8_t) DEFAULT_SWITCH_MODE; //momentary by default (we save it anyway) 


/**
 * espresso callback function to receive value and enable the toggle
 * when callback was initated by the sense task - no action is taken
 * */
void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t _on, void *_context) {
    switch(switch_mode) {
	//when toggle mode, flip the switch on or off, no matter the power state
	case switch_mode_toggle:
	    espresso_toggle(_on.bool_value);
	    break;
	//when momentary mode, cycle the switch. Mind that this event is called also by the sense task
	case switch_mode_momentary:
	    //called from cycling the switch manually (button, homekit or command)
	    if(espresso_sense_on.bool_value != _on.bool_value) 
		espresso_cycle();
	    break;
	default:
	    break;
    }
}

/**
 * cycle the momentary switch turning it on-and-off, this is used only in "momentary" mode
 * here we do not change the espresso_on value, we let sense mechanism to set the value
 * */
void espresso_cycle() {
    INFO("espresso_switch: <cycle momentary switch> current power state is: %s", espresso_sense_on.bool_value ? "on" : "off");
    gpio_write(GPIO_ESPRESSO_RELAY, 1);
    status_led_write(1);
    vTaskDelay(ESPRESSO_TOGGLE_TIME / portTICK_PERIOD_MS);
    gpio_write(GPIO_ESPRESSO_RELAY, 0);
    status_led_write(0);
}

/**
 * flip the switch to either on or off, this is used only in the "toggle" mode
 * */
void espresso_toggle(bool _on) {
    INFO("espresso_switch: <toggle switch> setting state = %s", _on ? "on" : "off" );
    gpio_write(GPIO_ESPRESSO_RELAY, _on);
    espresso_on.value.bool_value = _on;
    status_led_write(_on);
}

/***
 * change status of espresso switch from current to opposite
 * by either flipping the toggle or executing momentary 
 * */
void espresso_switch() {
	if (switch_mode == switch_mode_toggle)
	    espresso_toggle(espresso_on.value.bool_value ? 0 : 1);
	else
	    espresso_cycle();
}


/**
 * LED status light
 * */
void status_led_write(bool _on) {
    led_status = _on;
    gpio_write(GPIO_STATUS_LED, _on ? 0 : 1);
}

/**
 * monitor the status of espresso power
 * run this in a loop, find if the sense pin changed state
 * */
void espresso_sense_task() {
    //this is used to detect changes to the power status
    homekit_value_t previous_espresso_sense_on = { .bool_value = espresso_sense_on.bool_value };

    //keep monitoring by going idle for a predefined time and then sense again.
    //when status of the espresso changed - notify homekit
    while(1) {
    	vTaskDelay(ESPRESSO_SENSE_DELAY / portTICK_PERIOD_MS);

    	//by default read status from GPIO_ESPRESSO_SENSE. Otherwise read from simulation
	//sense gpio has pullup enabled and shorts to the GND when power is on
    	if(! simulation_enabled) espresso_sense_on.bool_value = ! gpio_read(GPIO_ESPRESSO_SENSE);
    	else espresso_sense_on.bool_value = simulate_on.bool_value; //read simulation value

	//detect changes to the power from previous and synchronise
	if (previous_espresso_sense_on.bool_value != espresso_sense_on.bool_value) {
	    INFO("espresso_switch: <sense> power status changed %s->%s", 
		   previous_espresso_sense_on.bool_value ? "on" : "off", espresso_sense_on.bool_value ? "on" : "off");
	    previous_espresso_sense_on.bool_value = espresso_sense_on.bool_value;
	}

	//ignore notifications about power state change when mode == toggle
    	//make sure LED indicates power status but only in momentary mode
	if (switch_mode == switch_mode_toggle) continue;
	else status_led_write(espresso_sense_on.bool_value);

	//when internal state different from homekit state - notify
	//also change the status value  of the espresso 
    	if (espresso_sense_on.bool_value != espresso_on.value.bool_value) {
	    //notify homekit, but this event is going to be ignored by espresso_on_callback
	    INFO("espresso_switch: <sense> power status is now = %s", espresso_sense_on.bool_value ? "on" : "off");
	    espresso_on.value.bool_value = espresso_sense_on.bool_value;
	    homekit_characteristic_notify(&espresso_on, espresso_sense_on);
    	}
    }

    vTaskDelete(NULL);
}

/**
 * identify accessort
 * */
void accessory_identify_callback(homekit_value_t _value) {
    INFO("espresso_switch: identify accessory");
    xTaskCreate(accessory_identify_task, "Accessory identify", 128, NULL, 2, NULL);
}

/**
 * show setup in the configuration app (eve)
 * */
void show_setup_callback() {
   save_settings();
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
 * taks to connect to NTP servers and get current time
 * SNTP initiation conflicts with mDNS, make sure this 
 * task is created only after homekit was started
 * */
void sntp_task(void *_args)
{
	const char *servers[] = {SNTP_SERVERS};

	/* Start SNTP */
	INFO("Starting SNTP... ");
	/* SNTP will request an update each SNTP_SYNC_PERIOD miliseconds  */
	sntp_set_update_delay(SNTP_SYNC_PERIOD);
	/* Set UTC zone, daylight savings off */
	const struct timezone tz = {0*60, 0};
	/* SNTP initialization */
	sntp_initialize(&tz);
	/* Servers must be configured right after initialization */
	sntp_set_servers(servers, sizeof(servers) / sizeof(char*));
	INFO("SNTP connection established");

	/* Print date and time and exit */
	vTaskDelay(5000 / portTICK_PERIOD_MS);
	time_t ts = time(NULL);
	printf("SYSTEM UTC TIME: %s", ctime(&ts));

	vTaskDelete(NULL);
}

/**
* callbck function for the holdpress on GPIO_BUTTON
*/
void on_button_holdpress_callback(uint8_t gpio, void* context) {
    INFO("espresso_switch: <button> registered holdpress on pin: %u", gpio);
    reset_settings();
}

/**
* callbck function for singlepress on GPIO_BUTTON
*/
void on_button_singlepress_callback(uint8_t gpio, void* context) {
    INFO("espresso_switch: <button> registered singlepress on pin: %u", gpio);
    espresso_switch();
}


/**
 * process commands
 * */
void on_command_callback(char* cmdline) {
    static char cmd_buffer[192];
    char *cmd = &cmd_buffer[0];
    char *arg1 = &cmd_buffer[64];
    char *arg2 = &cmd_buffer[128];

    //fill in arguments, apply safety
    sscanf(cmdline, "%63s %63s %63s", cmd, arg1, arg2);

    if(!strcmp(cmd, "reset")) {
	reset_settings();
    } else if (!strcmp(cmd, "setup_accessory")) {
	INFO("espresso_switch: setting up accessory with the: %s", cmdline );
	if (!strcmp(arg1,"mode") && !strcmp(arg2, "toggle")) {
	    INFO("espresso_switch: changing switch mode to %s", arg2 );
	    switch_mode = switch_mode_toggle;
	    save_settings();
	} else if (!strcmp(arg1,"mode") && !strcmp(arg2,"momentary")) {
	    INFO("espresso_switch: changing switch mode to %s", arg2 );
	    switch_mode = switch_mode_momentary;
	    save_settings();
	}
    } else if (!strcmp(cmd, "setup_wifi")) {
	INFO("espresso_switch: setting up wifi with the: %s", cmdline );
	wifi_config_set(arg1, arg2);
	wifi_config_get(&arg1, &arg2);
	INFO("espresso_switch: ssid = '%s', password = '%s', restarting...", arg1, arg2);
    	sdk_system_restart();
    } else if (!strcmp(cmd, "info_accessory")) {
	INFO("espresso_switch: info about the accessory, password: %s, mode: %s", homekit_config.password, switch_mode == switch_mode_momentary ? "momentary" : "toggle" );
    } else if (!strcmp(cmd, "info_wifi")) {
	INFO("espresso_switch: getting information about wifi connection");
	wifi_config_get(&arg1, &arg2);
	INFO("espresso_switch: ssid = '%s', password = '%s'", arg1, arg2);
    } else if( !strcmp(cmd, "reset_wifi") ) {
    	INFO("espresso_switch: resetting wifi settings");
    	wifi_config_reset();
    	sdk_system_restart();
    } else if( !strcmp(cmd, "reset_accessory") ) {
    	INFO("espresso_switch: resetting accessory pairing and settings");
    	homekit_server_reset();
    	sdk_system_restart();
    } else if( !strcmp(cmd, "reboot") ) {
    	INFO("espresso_switch: rebooting");
    	sdk_system_restart();
    } else if( !strcmp(cmd, "simulate_on") ) {
    	INFO("espresso_switch: Simulating espresso internal on");
    	simulation_enabled = true;
    	simulate_on.bool_value = true;
    } else if( !strcmp(cmd, "simulate_off") ) {
    	INFO("espresso_switch: Simulating espresso internal off");
    	simulation_enabled = true;
    	simulate_on.bool_value = false;
    } else if( !strcmp(cmd, "simulation_disable") ) {
    	INFO("espresso_switch: Disabling simulation");
    	simulation_enabled = false;
    } else if( !strcmp(cmd, "switch") ) {
    	INFO("espresso_switch: activate the switch");
    	simulation_enabled = false;
	espresso_switch();
    } else if( !strcmp(cmd, "status") ) {
	INFO("espresso_switch: espresso machine status: %s", espresso_sense_on.bool_value ? "on" : "off");
	espresso_status();
    } else if( !strcmp(cmd, "time") ) {
    	INFO("espresso_switch: reporting time of day");
    	time_t ts = time(NULL);
	printf("SYSTEM UTC TIME: %s", ctime(&ts));
    } else if( !strcmp(cmd, "help") ) {
    	INFO("espresso_switch: Available commands:\n\
    reboot - reboots the device, no changes to the settings\n\
    setup_wifi <ssid> <password> - sets wifi ssid and passwords and reboots \n\
    setup_accessory mode [momentary|toggle] - sets switch operation mode\n\
    info_accessory - provides information about current accessory setup \n\
    info_wifi - provides information about current wifi connction \n\
    reset - resets the device settings to factory\n\
    reset_accessory - resets pairing and accessory information and restarts homekit server\n\
    reset_wifi - resets wifi ssid and password and reboots\n\
    switch - turns the espresso machine on or off\n\
    simulate_on - simulates espresso power state on\n\
    simulate_off - simulates espresso power state off\n\
    simulation_disable - disable simulation\n\
    time - report current system time\n\
    status - returns the status of the espresso power circuit\n");
    }
}

/**
callback for events emitted by the homekit
currently serve only to start SNTP only when homekit was activated
 * */
void on_homekit_event_callback(homekit_event_t _event) {
    if (_event == HOMEKIT_EVENT_SERVER_INITIALIZED) {
	//wait a little for mDNS to activate
    	vTaskDelay(3000 / portTICK_PERIOD_MS);

	//start time SNTP client
	xTaskCreate(sntp_task, "SNTP", 1024, NULL, 1, NULL);	
    }
}

/**
 * called when wifi configuration was completed
 * this function starts the homekit server
 * */
void on_wifi_event_callback(wifi_config_event_t _event) {
    //when connected to network register homekit event handler 
    //and start homekit server
    if (_event == WIFI_CONFIG_CONNECTED && sdk_wifi_get_opmode() != STATION_MODE) {
	INFO("espresso_switch: connected to the network");
	INFO("espresso_switch: starting homekit server");
	homekit_config.on_event = on_homekit_event_callback;
	homekit_server_init(&homekit_config);
    }

    //when in AP mode, simply drive the status LED to indicate
    if (_event == WIFI_CONFIG_CONNECTED && sdk_wifi_get_opmode() != STATIONAP_MODE) {
	INFO("espresso_switch: running in AP mode");
	INFO("espresso_switch: starting homekit server");
	homekit_config.on_event = on_homekit_event_callback;
	homekit_server_init(&homekit_config);
    }
}


/**
 * generates accessory password from the chip_id, turns 32 bit chipID into 4-bit chunks and gets modulo 9 from each
 * and generates the custom section to be displayed with the wifi_config AP server
 * */
void homekit_password_init() {

    //generate random password and write to sysparams if no password yet
    //we initialise password with empty string, so it never is NULL
    if (homekit_config.password[0] ==0) {
	INFO("espresso_switch: no password available, generating new one");
      	uint8_t homekit_password[] = { hwrand() % 10, hwrand() % 10,hwrand() % 10,hwrand() % 10,hwrand() % 10,hwrand() % 10,hwrand() % 10,hwrand() % 10};
      	homekit_config.password = (char*) calloc( 12 , sizeof(char));

      	//write accessory password and save it
      	snprintf(homekit_config.password, 11, "%u%u%u-%u%u-%u%u%u", homekit_password[0],homekit_password[1],homekit_password[2],homekit_password[3],
	    homekit_password[4],homekit_password[5],homekit_password[6],homekit_password[7]);

	//save new password
	save_settings();
    }

    //write custom section with the password
    INFO("espresso_switch: accessory password: %s", homekit_config.password);
    char *buffer = (char*) calloc(strlen(homekit_config.password) + strlen(CUSTOM_HTML), sizeof(char));
    snprintf(buffer, strlen(homekit_config.password) + strlen(CUSTOM_HTML) + 1, CUSTOM_HTML, homekit_config.password);

    //set custom section. This is used in the wifi-config library
    wifi_config_set_custom_html(buffer);
}

/**
 * initialises button and button taks
 */
void button_init() {
    adv_button_set_evaluate_delay(10);
    adv_button_create(GPIO_BUTTON, true, false);
    adv_button_register_callback_fn(GPIO_BUTTON , on_button_holdpress_callback, button_event_type_holdpress, NULL);
    adv_button_register_callback_fn(GPIO_BUTTON , on_button_singlepress_callback, button_event_type_singlepress, NULL);

    INFO("espresso_switch: initialised hold-press button on pin: %d", GPIO_BUTTON);
}


/**
 * initialises the espresso state sense and prepare the toggle
 * this function launches the perpetual task to check the status of
 * of the espresso circuit and notifiy homekit on the status change
 * */
void espresso_init() {
    //enable ESPRESSO_RELAY pin for OUTPUT and ESPRESSO_SENSE for INPUT
    gpio_enable(GPIO_ESPRESSO_RELAY, GPIO_OUTPUT);
    gpio_enable(GPIO_STATUS_LED, GPIO_OUTPUT);
    gpio_enable(GPIO_ESPRESSO_SENSE, GPIO_INPUT);
    gpio_set_pullup(GPIO_ESPRESSO_RELAY, false, false);
    gpio_set_pullup(GPIO_ESPRESSO_SENSE, true, true);
    gpio_write(GPIO_ESPRESSO_RELAY, 0); //turn off the relay
    status_led_write(false);

    //report status to stdout
    espresso_status();

    //enable sense task
    xTaskCreate(espresso_sense_task, "Espresso Sense", 512, NULL, 1, NULL);
}

/**
 * reports espresso status to the stdout
 * */
void espresso_status() {
    INFO("espresso_switch: switch status: %s, power status: %s", espresso_on.value.bool_value ? "on" : "off", espresso_sense_on.bool_value ? "on" : "off");
    INFO("espresso_switch: espresso relay on gpio = %u, sense on gpio = %u and status led gpio = %u", GPIO_ESPRESSO_RELAY, GPIO_ESPRESSO_SENSE, GPIO_STATUS_LED);
    INFO("espresso_switch: accessory password = '%s' mode = %s", homekit_config.password, switch_mode == switch_mode_momentary ? "momentary" : "toggle");
    INFO("espresso_switch: status led = %s", led_status ? "enabled" : "disabled");
    INFO("espresso_switch: simulation = %s", simulation_enabled ? "enabled" : "disabled");
}

/**
 * restore configuration params from memory / sysparam settings
 * */
void restore_settings() {
    int8_t _switch_mode; //keeps retrieved value to further write it to volatile switch_mode
    char *bootstrapped = calloc(4, 1);

    INFO("espresso_switch: restoring settings")
    //find out if the device was bootstrapped
    sysparam_get_string(SYSPARAM_BOOTSTRAPPED, &bootstrapped);

    if (!strcmp(bootstrapped, "yes")) {
	INFO("espresso_switch: device already bootstrapped (bootstrapped = %s)", bootstrapped)
	sysparam_get_string("homekit_password", &homekit_config.password);
	sysparam_get_int8("switch_mode", &_switch_mode);
	switch_mode = _switch_mode;
    } else {
	INFO("espresso_switch: new device, performing initial setup")
	switch_mode = DEFAULT_SWITCH_MODE;
	save_settings();
    }

    //free buffer
    free(bootstrapped);
}

/**
 * restore configuration params from memory / sysparam settings
 * */
void save_settings() {
    INFO("espresso_switch: saving settings")
    sysparam_set_string(SYSPARAM_HOMEKIT_PASSWORD, homekit_config.password);
    sysparam_set_string(SYSPARAM_BOOTSTRAPPED, "yes"); //indicate that settings were saved at least once
    sysparam_set_int8(SYSPARAM_SWITCH_MODE, switch_mode);
}

/**
 * reset wifi, homekit and other settings
 * */
void reset_settings() {
    INFO("espresso_switch: resetting system");
    sysparam_set_string(SYSPARAM_BOOTSTRAPPED, "no");
    sysparam_set_string(SYSPARAM_HOMEKIT_PASSWORD, "");

    wifi_config_reset();
    homekit_server_reset();
    sdk_system_restart();
}

void user_init(void) {
    uart_set_baud(0, 74880); //using the same baud rate as boot loader (to not switch monitor)
    restore_settings();
    serial_cmdline_init(on_command_callback);
    wifi_config_init2("espresso-switch", NULL, on_wifi_event_callback); //using new API
    homekit_password_init(); //generate and set password if needed, must be called after wifi_config
    button_init();
    espresso_init();
}

