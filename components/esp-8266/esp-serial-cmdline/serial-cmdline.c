#include <stdlib.h>
#include <stdio.h>

#include <etstimer.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>
#include <string.h> 
#include "serial-cmdline.h"

#define INFO(message, ...) printf(">>> " message "\n", ##__VA_ARGS__);
#define ERROR(message, ...) printf("!!! " message "\n", ##__VA_ARGS__);

#ifndef CMD_BUFFER_SIZE
#define CMD_BUFFER_SIZE		64
#endif

#ifndef CMD_UART_NUM
#define CMD_UART_NUM		0
#endif

#define CMD_DELAY		1000

typedef struct {
    char *buffer;
    void  (*callback)(char*);
} serial_cmdline_config_t;

serial_cmdline_config_t  *serial_cmdline_config;


/**
 * listen for commands from the serial line
 * uses callback function passed at the initialisation
 * to process commands. Commands are not parameterised (yet)
 * */
void serial_cmdline_task() {
    uint8_t i = 0; //reset char counter
    char c = 0; //character to read

    while(1) {
	vTaskDelay(CMD_DELAY / portTICK_PERIOD_MS); //delay between consecutive read attempts
	memset(serial_cmdline_config->buffer, 0, CMD_BUFFER_SIZE); //reset bufer to zeros
	i = 0;
	c = 0;

	//read buffer until serial line is flushed
	while( (c = uart_getc_nowait(CMD_UART_NUM)) != '\xFF' && i < CMD_BUFFER_SIZE ) serial_cmdline_config->buffer[i++] = c;

	//replace newline with terminator
	if(serial_cmdline_config->buffer[0] > 0 && serial_cmdline_config->buffer[i-1] == '\n') serial_cmdline_config->buffer[i-1] = '\0'; 
    
	//process commands
	if(serial_cmdline_config->buffer[0] > 0) { 
	    serial_cmdline_config->callback(serial_cmdline_config->buffer); //run command interpreter
	    memset(serial_cmdline_config->buffer, 0, CMD_BUFFER_SIZE); //reset bufer to zeros
	}
    }

    vTaskDelete(NULL);
}


/**
 * initialises serial line listener
 * */
void serial_cmdline_init( void (*callback)(char*) ){
    INFO("serial-cmdline: staring serial listener");    

    //set the callback function
    serial_cmdline_config = malloc(sizeof(serial_cmdline_config_t));
    serial_cmdline_config->buffer = calloc(CMD_BUFFER_SIZE, sizeof(char)); 
    serial_cmdline_config->callback = callback;

    //listen for what is sent over the serial line
    xTaskCreate(serial_cmdline_task, "Command Listener", 768, NULL, 0, NULL);
}


