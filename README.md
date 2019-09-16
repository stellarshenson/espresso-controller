# espresso-controller

## Homekit Enabled Rancillio Espresso Controller ##
Homekit enabled Rancilio Espresso Controller for Rancilio Silvia v5 Espresso Machine

![rancilio silvia](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/rancilio-silvia.jpeg)

this project was possible thanks to the freeRTOS and esp-open-sdk
Also thanks to folowing other projects:
* [maximkulkin/esp-homekit](https://github.com/maximkulkin/esp-homekit.git)
* [maximkulkin/esp-wifi-config](https://github.com/maximkulkin/esp-wifi-config)
* [ravensystem/esp-adv-button](https://github.com/RavenSystem/esp-adv-button.git)

This module is specifically designed to control turning on-and-off Rancilio Silvia v5 Espresso Machine.
Rancilio Silvia has only a momentary switch that while toggled, powers the machine on (when previously off) and off (when previously on).
Additionally Rancilio Silvia uses an internal timer that turns the machine off after 30min

Espresso Controller monitors the internal power state of the espresso machine and controls powering the machine up and down when activated

### Typical Circuit Layout###
You would need the following parts to complete the build
* Wemos D1 Mini <any>
* Optocoupler + 330 Resistor
* Relay (3.3V level or Relay 5v + NPN transistor and a couple of passive jellybeans)
* 1 pull-down resistor (33k is ok)
* Status LED + 330 Resistor
* HI-Link 5V power module (to power the thing up from mains)

![circuit layout](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/misc/espresso_switch_bb.png)
