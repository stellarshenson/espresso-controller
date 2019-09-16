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

### Typical Circuit Layout ###
You would need the following parts to complete the build
* Wemos D1 Mini <any> - any wemos with 4Mb+ flash works (Mini or Mini Pro)
* Optocoupler + 330 Resistor - used for powersense. The Rancilio Silvia 12V power indicator circuit it very noisy, we would use the optocoupler to provide galvanic isolation between the controller and the espresso machine
* Relay (3.3V level or Relay 5v + NPN transistor and a couple of passive jellybeans) - this needs to switch the 12v noisy circuit. MOSFET will also do, but I'd prefer those to be galvanicaly isolated
* 1 pull-down resistor (33k is ok) - sense circuit is LOW by default and HIGH when 12V power indicator circuit energises the optocoupler
* Status LED + 330 Resistor - this is just a status LED. Fast blink = starting up, Slow blink - AP mode, No blink - connected to network 
* HI-Link 5V power module (to power the thing up from mains) - it would be preferred to connect the controller to the mains terminals at the Rancilio power brick. I am figuiring out other options, stay tuned. Voltage for the Wemos D1 must be relatively clean.

![circuit layout](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/espresso_switch_bb.png)
![power brick](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/rancilio-brain-1.jpeg)

TBD: circuit schematics, PCB layout and the operation video

### Installation ###
TBD
