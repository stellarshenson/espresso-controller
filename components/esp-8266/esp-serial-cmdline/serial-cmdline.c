#include <stdlib.h>

#include <etstimer.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>
#include <string.h> 


#include "serial-cmdline.h"

typedef struct {
    char *buffer;
    void  (*callback)(char*);
} serial_cmdline_config_t;

serial_cmdline_config_t  *config;


/**
 * listen for commands from the serial line
 * uses callback function passed at the initialisation
 * to process commands. Commands are not parameterised (yet)
 * */
void serial_cmdline_task() {
    uint8_t i = 0; //reset char counter
    char c = 0; //character to read

    while(1) {
	vTaskDelay(500 / portTICK_PERIOD_MS); //delay between consecutive read attempts
	i = 0;
	c = 0;

	//read buffer until serial line is flushed
	while( (c = uart_getc_nowait(CMD_UART_NUM)) != '\xFF' && i < CMD_BUFFER_SIZE ) config->buffer[i++] = c;

	//replace newline with terminator
	if(strlen(config->buffer) > 0 && config->buffer[i-1] == '\n') config->buffer[i-1] = '\0'; 
    
	//process commands
	if(strlen(config->buffer) > 0) { 
	    config->callback(config->buffer); //run command interpreter
	    memset(config->buffer, 0, CMD_BUFFER_SIZE); //reset bufer to zeros
	}
    }

    vTaskDelete(NULL);
}


/**
 * initialises serial line listener
 * */
void serial_cmdline_init( void (*callback)(char*) ){
    //set the callback function
    config = malloc(sizeof(serial_cmdline_config_t));
    config->buffer = calloc(CMD_BUFFER_SIZE, sizeof(char)); 
    config->callback = callback;

    //listen for what is sent over the serial line
    xTaskCreate(serial_cmdline_task, "Command Listener", 1024, NULL, 4, NULL);
}


