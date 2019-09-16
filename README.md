## Homekit Enabled Rancillio Espresso Controller ##
Homekit enabled Rancilio Espresso Controller for Rancilio Silvia v5 Espresso Machine

![rancilio silvia](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/rancilio-silvia-mine.jpeg)

this project was possible thanks to the freeRTOS and esp-open-sdk
Also thanks to folowing other projects:
* [maximkulkin/esp-homekit](https://github.com/maximkulkin/esp-homekit.git)
* [maximkulkin/esp-wifi-config](https://github.com/maximkulkin/esp-wifi-config)
* [ravensystem/esp-adv-button](https://github.com/RavenSystem/esp-adv-button.git)

This module is specifically designed to control turning on-and-off Rancilio Silvia v5 Espresso Machine.
Rancilio Silvia has only a momentary switch that while toggled, powers the machine on (when previously off) and off (when previously on).
Additionally Rancilio Silvia uses an internal timer that turns the machine off after 30min

Espresso Controller monitors the internal power state of the espresso machine and controls powering the machine up and down when activated

### Firmware Build ###
See [build firmware](https://github.com/stellarshenson/espresso-controller/wiki/build-firmware) wiki page for the reference

### Functionality ###
The device is supposed to control the powering up and down the espresso machine and notify any power changes to the Homekit clients nearby. In the future the device will be able to control the auto-shutdown of the espresso machine (powersaving) and flushing (running water through the group after warm-up). Additionally the firmware will monitor the boiler temperature in the future.

Currently the device extends the following number of output interfaces:
* __Toggle interface__ - controls the toggle switch and works exactly like the momentary switch on the espresso machine front panel
* __Power sense interface__ - senses whether the machine is on or off (and provides notifications to the homekit clients)
* __Status LED__ - indicates the status of the device, fast blink = booting up, slow-blink = AP mode, no blink = connected to the network, SOS blink (3 short, 3 long, 3 short) = problem

Additionally, when connected through the microUSB port to the computer, the device outputs serial diagnostics messages and extends serial commandline. Type *help* to get the list of available commands.

The serial inteface was configured with the __74880 baud rate__

### Typical Circuit Layout ###
You would need the following parts to complete the build
* __Wemos D1 Mini <any>__ - any wemos with 4Mb+ flash works (Mini or Mini Pro)
* __Optocoupler + 330 Resistor__ - used for powersense. The Rancilio Silvia 12V power indicator circuit it very noisy, we would use the optocoupler to provide galvanic isolation between the controller and the espresso machine
* __Relay__ (3.3V level or Relay 5v + NPN transistor and a couple of passive jellybeans) - this needs to switch the 12v noisy circuit. MOSFET will also do, but I'd prefer those to be galvanicaly isolated
* __1 pull-down resistor (33k is ok)__ - power sense circuit is LOW by default and HIGH when 12V power indicator circuit energises the optocoupler
* __1 Status LED + 330 Resistor__ - this is just a status LED. Fast blink = starting up, Slow blink - AP mode, No blink - connected to network 
* __HI-Link 5V power module__ (to power the thing up from mains) - it would be preferred to connect the controller to the mains terminals at the Rancilio power brick. I am figuiring out other options, stay tuned. Voltage for the Wemos D1 must be relatively clean.Wemos has onboard a small 3v3 linear power supply controller. Please keep in mind that Wemos D1 uses 3v3 logic levels :-)

I will publish the full BOM as soon as I finish the PCB build and installation

![circuit layout](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/espresso_switch_bb.png)
![power brick](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/rancilio-brain-annotated.png)

TBD: circuit schematics, PCB layout and the operation video

### Installation ###
TBD
