#include <stdlib.h>

#include <etstimer.h>
#include <esp/uart.h>
#include <esp8266.h>
#include <FreeRTOS.h>
#include <task.h>
#include <string.h> 


#include "serial-commands.h"

void user_init(void) {
    uart_set_baud(0, 115200);
}
