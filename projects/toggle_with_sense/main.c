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

#include <homekit/homekit.h>
#include <homekit/characteristics.h>
#include <wifi_config.h>
#include <espressif/esp_system.h>

#define GPIO_ESPRESSO_TOGGLE	2
#define GPIO_ESPRESSO_SENSE	4
#define ESPRESSO_SENSE_DELAY	500

void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context);
homekit_characteristic_t espresso_on = HOMEKIT_CHARACTERISTIC_(ON, false, .callback=HOMEKIT_CHARACTERISTIC_CALLBACK(espresso_on_callback));
void espresso_sense_task();


/**
 * toggle the switch
 * */
void espresso_toggle(bool on) {
    //gpio_write(GPIO_ESPRESSO_TOGGLE, on ? 0 : 1);
    gpio_write(GPIO_ESPRESSO_TOGGLE, 1);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    gpio_write(GPIO_ESPRESSO_TOGGLE, 0);
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
    //espresso_toggle(espresso_on.value.bool_value);
    
    //enable sense task
    xTaskCreate(espresso_sense_task, "Espresso Sense", 128, NULL, 2, NULL);
}


/**
 * run this in a loop, find if the sense pin changed state
 * */
void espresso_sense_task() {
    //monitor the status of espresso power
    homekit_value_t on;
    on.bool_value = false;

    //get the status and notify homekit
    on.bool_value = gpio_read(GPIO_ESPRESSO_TOGGLE);
    homekit_characteristic_notify(&espresso_on, on);


    //keep monitoring by going idle for a predefined time and then sense again.
    //when status of the espresso changed - notify homekit
    while(1) {
	vTaskDelay(ESPRESSO_SENSE_DELAY / portTICK_PERIOD_MS);
	on.bool_value = gpio_read(GPIO_ESPRESSO_TOGGLE);
	if( on.bool_value != espresso_on.value.bool_value ) homekit_characteristic_notify(&espresso_on, on);
    }

}

void espresso_on_callback(homekit_characteristic_t *_ch, homekit_value_t on, void *context) {
    espresso_toggle(espresso_on.value.bool_value);
}

void led_identify_task(void *_args) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            espresso_toggle(true);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            espresso_toggle(false);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        vTaskDelay(250 / portTICK_PERIOD_MS);
    }

    espresso_toggle(espresso_on.value.bool_value);

    vTaskDelete(NULL);
}

void led_identify(homekit_value_t _value) {
    printf("LED identify\n");
    xTaskCreate(led_identify_task, "LED identify", 128, NULL, 2, NULL);
}


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]){
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Sample LED"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "HaPK"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "037A2BABF19D"),
            HOMEKIT_CHARACTERISTIC(MODEL, "MyLED"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "0.1"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, led_identify),
            NULL
        }),
        HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Sample LED"),
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
    .password = "000-00-000"
};

void on_wifi_ready() {
    homekit_server_init(&config);
}

/**
 * generates accessory ID from the chipID, turns 32 bit chipID into 4-byte chunks and gets modulo 9 from each
 * */
void accessory_id_init() {
    uint32_t chipid = sdk_system_get_chip_id();
    uint8_t accessory_id_digits[] = { chipid >> 0 & 0xf % 9,  chipid >> 4 & 0xf % 9, chipid >> 8 & 0xf % 9, 
    	chipid >> 12 & 0xf % 9, chipid >> 16 & 0xf % 9, chipid >> 20 & 0xf % 9, chipid >> 24 & 0xf % 9, chipid >> 28 & 0xf % 9 }; 
    config.password = (char*) malloc( 11 * sizeof(char));
    snprintf(config.password, 11, "%u%u%u-%u%u-%u%u%u", accessory_id_digits[0], accessory_id_digits[1], accessory_id_digits[2], 
    	                               accessory_id_digits[3], accessory_id_digits[4], accessory_id_digits[5], accessory_id_digits[6], accessory_id_digits[7]);
    accessory_id_set(config.password);
}


void user_init(void) {
    uart_set_baud(0, 115200);
    accessory_id_init();
    wifi_config_init("stellars", NULL, on_wifi_ready);
    espresso_init();
}
