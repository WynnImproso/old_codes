#include <dht.h>
#include <LiquidCrystal.h>

#define dht_dpin A0 //no ; here. Set equal to channel sensor is on

dht DHT;
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);

void setup(){
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);
  delay(300);//Let system settle
  Serial.println("Humidity and temperature\n\n");
  delay(700);//Wait rest of 1000ms recommended delay before
  //accessing sensor
}//end "setup()"

void loop(){
  //This is the "heart" of the program.
  DHT.read11(dht_dpin);

    lcd.setCursor(0, 0);
    lcd.print("%RH = ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.print(DHT.temperature);
    lcd.print("C"); 

  //Don't try to access too frequently... in theory
  //should be once per two seconds, fastest,
  //but seems to work after 0.8 second.
   // when characters arrive over the serial port...
   
  delay(10000);
}// end loop()
