# espresso-controller
Homekit enabled Rancilio Espresso Controller

Module specifically designed to control tunring on-and-off Rancilio Silvia v5 Espresso Machine.
Rancilio Silvia has only a momentary switch that while toggled, powers the machine on (when previously off) and off (when previously on).
Additionally Rancilio Silvia uses an internal timer that turns the machine off after 30min

Espresso Controller monitors the internal power state of the espresso machine and controls powering the machine up and down when activated

Example circuit layout
![circuit layout](https://github.com/stellarshenson/espresso-controller/blob/master/projects/espresso_switch/fritzing/espresso_switch_bb.png)
