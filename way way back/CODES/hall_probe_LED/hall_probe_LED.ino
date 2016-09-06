//program for magnetic equipotential line plotting
// data can be stored in sd card
//programmed by nelio c. altoveros and hazel joyce m.ramirez
//october 7, 2013


#include <SD.h>
#include <stdio.h>
#include<LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);

const float m=12.706;  //slope
const float b=-31.366; //intercept
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
//const int analogInPin2 = A2;  // Analog input pin that the potentiometer is attached to
const int PB = 1;             //push button
const int LED = 3;           //buzzer
int n=50;          //50 samples

int sensorValue1 = 0;    //preset value
int sensorValue2 = 0;    //continuous readout 
long int start;
float volts1=0.0;
float volts2=0.0;
float tesla1=0.0;
float tesla2=0.0;
long ttime=0;
float diff=0.01;


void setup() {
  pinMode(10, OUTPUT);
  pinMode (LED, OUTPUT);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Magnetic Field");
  lcd.setCursor(0,1);
  lcd.print("E Plotting");
  delay(5000);
  
}


void lcdDisplayData()
{
  lcd.setCursor(0,0);
  lcd.print("SB(mT): ");
  lcd.setCursor(8,0);
  lcd.print(tesla1,2);
  lcd.setCursor(13,0);
  lcd.print("    ");
  
  
  lcd.setCursor(0,1);
  lcd.print("B(mT): ");
  lcd.setCursor(8,1);
  lcd.print(tesla2,2);
  lcd.setCursor(13,1);
  lcd.print("    ");
  
}



void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place probe on ");
  lcd.setCursor(0,1);
  lcd.print("E Plotting Board");  
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press button");
  lcd.setCursor(0,1);
  lcd.print("to store value");
  delay(5000); 

  while(digitalRead(PB)==HIGH) {}
    lcd.clear();
    start=millis();
    sensorValue1=0.0;
    for (int i=0;i<n;i++) {
     sensorValue1 += analogRead(analogInPin1);
  }
    volts1=(sensorValue1*5.0)/(n*1023.0);
  tesla1=m*volts1+b;
  while (1) {
  if (digitalRead(PB)==LOW) {
    sensorValue1=0.0;
     for (int i=0;i<n;i++) {
     sensorValue1 += analogRead(analogInPin1);
     } 
     volts1=(sensorValue1*5.0)/(n*1023.0);
     tesla1=m*volts1+b;
  }
  ttime= (millis()-start);
  sensorValue2=0.0;
  for (int i=0;i<n;i++) {
     sensorValue2 += analogRead(analogInPin1);
  }
  volts2=(sensorValue2*5.0)/(n*1023.0);
  tesla2=m*volts2+b;
  ttime= (millis()-start);
  if (abs(volts1-volts2)<=diff) {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    
  }
  Serial.print(tesla1,5);
  Serial.print("\t");  
  Serial.println(tesla2,5); 
  lcdDisplayData(); 
  delay(500);
  }
}


