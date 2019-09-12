/*
 * simple serial command line driver
 *
 * this driver uses non-blocking I/O on the UART
 * serial line 0 and launches the serial listener
 * as freertos task
 *
 */

/**
 * this function initialises the listener and starts the 
 * the command interpreter task (it runs asynchronously)
 * */
void serial_cmdline_init( void (*callback)(char*) );

