# UVGI-Lamp-timer
Small arduino working hours timer 

Little project to monitor work hours of UV-C lamp used as germicidal irradioation system. 
Lamp was made here in Poland for hospitals and any possible use in case of COVID-19 danger.
Thanks to my friend Artur for brilliant idea and whole UVGI lamp construction
Program for arduino boards to memorize in EEPROM: on/off cycles, lamp working hours
 
To do: change lamp indication (add hardware button) 

To detect power off, add a voltage divider and monitor the voltage across the divider through A0. Connect the arduino power supply through a diode and then give a 1000uF electrolytic capacitor to keep powering during EEPROM writes
Done in simple loop without interrupts
