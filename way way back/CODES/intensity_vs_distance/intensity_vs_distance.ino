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
const int pingPin = 5;

const int chipSelect = 10;
 

const int TRIG_PIN = 3;
const int ECHO_PIN = 5;

unsigned long time;
 
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
   lcd.setCursor(0,0);
  double ave = 0.0;
//  double ave1 =0.0;
//  double ave2 = 0.0;
  int i = 0;
  int sensorf, sensorf1, sensorf2;
  int sensor[5];
//  int sensor1[5];
//  int sensor2[5];

//take five (5) readings from A0 A1 and A2 and get average for data processing  
for (i=0; i<5 ; i++){

  sensor[i] = analogRead(0); 
//  sensor1[i] = analogRead(1); 
//  sensor2[i] = analogRead(2);  
}
 sensorf = sensor[0] + sensor[1] + sensor[2] +sensor[3] + sensor[4];
 ave = sensorf/5;
// sensorf1 = sensor1[0] + sensor1[1] + sensor1[2] +sensor1[3] + sensor1[4];
// ave1 = sensorf1/5;
// sensorf2 = sensor2[0] + sensor2[1] + sensor2[2] +sensor2[3] + sensor2[4];
// ave2 = sensorf2/5;
// ldr(ave,ave1,ave2);
   ldr(ave);
  }

//convert ADC value to light intensity
void ldr(int sensor) { 
  double volt = sensor * (5.0/1024.0);
//  double volt1 = sensor1 * (5.0/1024.0);
//  double volt2 = sensor2 * (5.0/1024.0);
  
  double res = (10.0 * 5.0) / volt - 10.0;
//  double res1 = (10.0 * 5.0) / volt1 - 10.0;
//  double res2 = (10.0 * 5.0) / volt2 - 10.0; 
  
// Calculating the intensity of light in lux and display in LCd and serial
  double lx = 255.84 * pow(res, -10/9);
//  double lx1 = 255.84 * pow(res1, -10/9);
//  double lx2 = 255.84 * pow(res2, -10/9); 
  lcd.print("I=");
  lcd.print(lx);
  lcd.print(" ");
  lcd.setCursor(0,0);
//  lcd.print("B=");
//  lcd.print(lx1); 
//  lcd.print(" ");
//  lcd.setCursor(0,1);
//  lcd.print("C=");
//  lcd.print(lx2);
//  lcd.print(" ");
  //delay(1000);
  time = millis();
  time=time/1000;
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
    
    lcd.setCursor(0,1);
    lcd.print("d:");
    lcd.setCursor(3,1);
    lcd.print(distanceCm);
    lcd.print(" cm        ");
  }
  delay(1000);
}
//void loop() {
 
//  Serial.println(time);
//
//  Serial.println(lx);
//  Serial.println(lx1);
//  Serial.println(lx2);
//  Serial.println(" ");

