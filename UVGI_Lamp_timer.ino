/* 
 UVGI Lamp working hour timer (c) Sebart 2020  sebart@agabox.net
 Little project to monitor work hours of UV-C lamp 
 used as germicidal irradioation system 
 made here in Poland for hospitals and any possible use in case of *COVID-19 danger
 Thanks to my friend Artur for brilliant idea and whole UVGI lamp construction
 Program for arduino boards to memorize in EEPROM: on/off cycles, lamp working hours
 
 To do: change lamp indication (add hardware button) 

eepointer + 0 - seconds
eepointer + 1 - minutes
eepointer + 2 - workhour LSB
eepointer + 3 - workhour MSB
eepointer + 4 - pwrcycle LSB
eepointer + 5 - pwrcycle MSB

*/

#include <LiquidCrystal.h>
#include "EEPROM.h"
// initialize the LCD library with the numbers of the interface pins (RS,E,D4,D5,D6,D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define maxworkhours 8000;  // maximum work hours for the lamp
#define eepointer 100 // eeprom adres pointer  

static char timestr[11] = "-----:--:--";  // LCD template

unsigned long millis_last;
unsigned long millis_curr;
char sec = 00;
char minute = 00;
unsigned int workhour = 0;
unsigned int pwr_cycle = 0;
unsigned int licz = 0;
int volt_last;
int volt_curr;

void setup() 
{

sec = EEPROM [eepointer];
minute = EEPROM [eepointer+1];
workhour = EEPROM[eepointer+2] + 256*EEPROM[eepointer+3];
pwr_cycle = EEPROM[eepointer+4] + 256*EEPROM[eepointer+5] + 1;

//licz = workhour;
//for (char i=4; i>=0; i--)
//{
//timestr[i] = '0' + licz %10; 
//licz = licz/10;
//};
  
 lcd.begin(16, 2);
 
 lcd.setCursor(0, 0);
 lcd.print("UVGI Lamp Timer");
 delay (2000);
 
 lcd.setCursor(0, 0);
 lcd.print("Power cycles:  ");
 lcd.setCursor(0, 1);
 lcd.print(pwr_cycle);
 delay (2000);
 
 lcd.setCursor(0, 0);
 lcd.print("UVGI lamp time:");
 lcd.setCursor(0, 1);
 lcd.print("              ");
  
  
  volt_last = analogRead(0);
  
  delay(10);
}


void loop() {
  millis_curr = millis();
  volt_curr = analogRead (0);
  if (millis_curr - millis_last > 1000) // every second
    {
      millis_last = millis();
      sec ++;
      if (sec == 60) {sec = 0; minute++;};
      if (minute == 60) {minute = 0; workhour++;};
//      lcd.setCursor(12, 0); lcd.print(sec);

     licz = workhour;
     for (char i=4; i>=0; i--)
      {
      timestr[i] = '0' + licz %10; 
      licz = licz/10;
      };
     timestr[6] = '0' + minute / 10;
     timestr[7] = '0' + minute % 10;
     timestr[9] = '0' + sec / 10;
     timestr[10] = '0' + sec % 10;
       
     lcd.setCursor(0, 1);
     for (int i=0; i<11; i++) 
        {
        lcd.write(timestr[i]);
        };
    };
   
 if (volt_last - volt_curr > 50)   // power drop detection 50 = 0.5 V drop
    {
     EEPROM[eepointer] = sec;
     EEPROM[eepointer+1] = minute;
     EEPROM[eepointer+2] = workhour % 256;
     EEPROM[eepointer+3] = workhour / 256;
     EEPROM[eepointer+4] = pwr_cycle % 256;
     EEPROM[eepointer+5] = pwr_cycle / 256;
     while(1) {};
     }
 volt_last = analogRead(0);
 delay(1);  
}
