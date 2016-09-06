/*
Tested with HY-SRF05, HC-SR04
Assuming a room temp of 20 degrees centigrade
The circuit:
	* VVC connection of the sensor attached to +5V
	* GND connection of the sensor attached to ground
	* TRIG connection of the sensor attached to digital pin 12
        * ECHO connection of the sensor attached to digital pin 13
*/
#include<LiquidCrystal.h>
#include <SD.h>
#include <string.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);
// this constant won't change.  It's the pin number
// of the sensor's output:
//const int pingPin = 5;

const int chipSelect = 10;
 

const int TRIG_PIN = 3;
const int ECHO_PIN = 5;
 
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
 
  lcd.begin(16,2);
  lcd.clear();
  
  pinMode(10, OUTPUT);
 
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}
 
void loop()
{
   double duration, distanceCm, distanceIn;
 
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);
 
  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;
  distanceIn = duration / 74 / 2;
 
  if (distanceCm <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distanceIn);
    Serial.print("in, ");
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
    
    lcd.setCursor(0,0);
    lcd.print("Distance:           ");
    lcd.setCursor(0,1);
    lcd.print(distanceCm);
    lcd.print(" cm        ");
  }
  delay(1000);
}
