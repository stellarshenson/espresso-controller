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

#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <wifi_config.h>
#include <espressif/esp_system.h>

#define GPIO_ESPRESSO_TOGGLE	2
#define GPIO_LED		2
#define GPIO_ESPRESSO_SENSE	4
#define ESPRESSO_SENSE_DELAY	1500

//pairing password to display, this will be embedded in the AP homepage
#define CUSTOM_SECTION "<p><b>Homekit Accessory ID:</b><br> %s </p>"
#define INITIAL_ACCESSORY_PASSWORD "000-00-000"

void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context);
homekit_characteristic_t espresso_on = HOMEKIT_CHARACTERISTIC_(ON, false, .callback=HOMEKIT_CHARACTERISTIC_CALLBACK(espresso_on_callback));
void espresso_sense_task();
void espresso_toggle(bool on);
void led_write(bool on);
void accessory_identify_task(void *_args);


/**
 * espresso callback function to receive val
 * */
void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context) {
    espresso_toggle(on.bool_value);
}

/**
 * toggle the switch
 * */
void espresso_toggle(bool on) {
    //gpio_write(GPIO_ESPRESSO_TOGGLE, on ? 0 : 1);
    printf("espresso toggle %u\n", on);
    gpio_write(GPIO_ESPRESSO_TOGGLE, 1);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    gpio_write(GPIO_ESPRESSO_TOGGLE, 0);

    //set value
    espresso_on.value.bool_value = on;
    led_write(on);
}

/**
 * LED status light
 * */
void led_write(bool on) {
    printf("led state: %u\n", on );
    gpio_write(GPIO_LED, on ? 0 : 1);
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
    gpio_set_pullup(GPIO_ESPRESSO_TOGGLE, false, false);
    gpio_set_pullup(GPIO_ESPRESSO_SENSE, false, false);
    led_write(false);
    
    //enable sense task
    xTaskCreate(espresso_sense_task, "Espresso Sense", 512, NULL, 3, NULL);
}


/**
 * run this in a loop, find if the sense pin changed state
 * */
void espresso_sense_task() {
    //monitor the status of espresso power
    homekit_value_t on;

    //get the status and notify homekit
    //on.bool_value = gpio_read(GPIO_ESPRESSO_TOGGLE);
    //bool on = gpio_read(GPIO_ESPRESSO_TOGGLE);
    //homekit_characteristic_notify(&espresso_on, on);


    //keep monitoring by going idle for a predefined time and then sense again.
    //when status of the espresso changed - notify homekit
    while(1) {
	vTaskDelay(ESPRESSO_SENSE_DELAY / portTICK_PERIOD_MS);
	//on.bool_value = gpio_read(GPIO_ESPRESSO_TOGGLE);
	on.bool_value = (rand() % 10 == 0 ? 0 : 1);
	//gpio_read(GPIO_ESPRESSO_TOGGLE);
	//printf("espresso sense, status:  %d\n", on.bool_value);
	printf("espresso sense: %d\n", on.bool_value);
	if( on.bool_value != espresso_on.value.bool_value ) homekit_characteristic_notify(&espresso_on, on);
    }

    vTaskDelete(NULL);
}

/**
 * identify accessort
 * */
void accessory_identify(homekit_value_t _value) {
    printf("Accessory identify\n");
    xTaskCreate(accessory_identify_task, "Accessory identify", 128, NULL, 2, NULL);
}

/**
 * task run to identify the accessory
 * */
void accessory_identify_task(void *_args) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            led_write(true);
            vTaskDelay(100 / portTICK_PERIOD_MS);
             led_write(false);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        vTaskDelay(250 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]){
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Espresso Switch"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Stellars"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "001"),
            HOMEKIT_CHARACTERISTIC(MODEL, "Momentary Switch"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.3"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL
        }),
        HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Espresso Switch"),
            &espresso_on,
            NULL
        }),
        NULL
    }),
    NULL
};

/**
 * initialise server config with the accessory and the initial zeroerd password
 * password will be further replaced with the generated one with accessory_id_init()
 * */
homekit_server_config_t config = {
    .accessories = accessories,
    .password = INITIAL_ACCESSORY_PASSWORD
};

void on_wifi_ready() {
    homekit_server_init(&config);
}

/**
 * generates accessory password from the chip_id, turns 32 bit chipID into 4-bit chunks and gets modulo 9 from each
 * and generates the custom section to be displayed with the wifi_config AP server
 * */
void accessory_password_init() {
    uint32_t chipid = sdk_system_get_chip_id();
    uint8_t accessory_id_digits[] = { chipid >> 0 & 0xf % 9,  chipid >> 4 & 0xf % 9, chipid >> 8 & 0xf % 9, 
    	chipid >> 12 & 0xf % 9, chipid >> 16 & 0xf % 9, chipid >> 20 & 0xf % 9, chipid >> 24 & 0xf % 9, chipid >> 28 & 0xf % 9 }; 
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
    custom_section_set(buffer);
}


void user_init(void) {
    uart_set_baud(0, 74880);
    accessory_password_init();
    wifi_config_init("stellars", NULL, on_wifi_ready);
    espresso_init();
}
