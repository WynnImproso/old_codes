// Display temperature in LCD using LM35 temperature sensor
//#include<LiquidCrystal.h>
// Initialize the library with the numbers of the interface pins
unsigned long time;
//LiquidCrystal lcd(7, 8, 9, 2, 4, 6);
#include <vLib.h>
vLib vlib;

void setup() {
Serial.begin(9600);
//lcd.begin(16,2);
vlib.lcdInitialize(9,8);
analogReference(INTERNAL);
}

void loop() {
int sensorf,i;
int sensor[5];
double ave;

  vlib.lcdCmd(0x80);
  time = millis();
  time=time/1000;
  Serial.print(time);
  Serial.print("\t");

//take five (5) readings from A0 A1 and A2 and get average for data processing  
for (i=0; i<5 ; i++){

  sensor[i] = analogRead(0); 
}
 sensorf = sensor[0] + sensor[1] + sensor[2] +sensor[3] + sensor[4];
 ave = sensorf/5;

  int temp = ave * 0.09765625; // Convert to C
//  double temp = ((((ave * 5 )/1024)-0.881)*100)-0.6;
  vlib.lcdPrint("temp: ");
  vlib.lcdPrint(temp);
  vlib.lcdPrint(" C     ");
  
  Serial.println(temp);

  
  delay(1000); 

}

