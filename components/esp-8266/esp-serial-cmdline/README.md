esp-serial-cmdline
==============

Library for [ESP-OPEN-RTOS](https://github.com/SuperHouse/esp-open-rtos)
to communicate with the device with the use of UART serial line

Developer would need to define a callback function to interpret the commands
and supply as parameter to the initialisation function 


```c
// example on_command handler
void on_command(char* cmd) {
    if(!strcmp(cmd, "reboot")) {
	printf("rebooting\n");
	sdk_system_restart();
    } else if( !strcmp(cmd, "help") ) {
	printf("Available commands:\n\
	reboot - reboots the device, no changes to the settings\n");
    }
}


void user_init(void) {
    //initialise command listener with on_command callback
    serial_cmdline_init( on_command ); 
}
```

License
=======

MIT licensed. See the bundled [LICENSE](https://github.com/maximkulkin/esp-led-status/blob/master/LICENSE) file for more details.
