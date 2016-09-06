//VISSER program for charging and discharging of capacitor
// data can be stored in sd card

#include <SD.h>
#include <stdio.h>
#include<LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);

const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;    // value read from the pot
long int start;
float volts=0.0;
long ttime=0;

void setup() {
  pinMode(10, OUTPUT);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Charging and");
  lcd.setCursor(0,1);
  lcd.print("Discharging of C");
  delay(5000);
  
}


void lcdDisplayData()
{
  lcd.setCursor(0,0);
  lcd.print("T(ms): ");
  lcd.setCursor(7,0);
  lcd.print(ttime);
  lcd.setCursor(0,1);
  lcd.print("Vc(volts): ");
  lcd.setCursor(10,1);
  lcd.print(volts,2);
}



void loop() {
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Flip to Charge");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Data is being");
  lcd.setCursor(0,1);
  lcd.print("collected...  ");
  delay(2000);
  lcd.clear();
  start=millis();
  while (1) {
  sensorValue = analogRead(analogInPin);
  volts=(sensorValue*5.0)/(1023.0);
  ttime= (millis()-start);
  Serial.print(ttime);
  Serial.print("\t");  
  Serial.println(volts,5); 
  lcdDisplayData(); 
  
  }
}


