//#include <LiquidCrystal.h>
//LiquidCrystal lcd(7, 8, 9, 2, 4, 6);
#include <vLib.h>
vLib vlib;
//RGB LED pins

int sensor = 0;
float ave = 0;

void setup (){
  Serial.begin(9600);
  vlib.lcdInitialize(9,8);
//  lcd.begin(16,2);
  vlib.lcdCmd(0x80); // Prints in the first line
  vlib.lcdPrint("Rel Intensity");  
//  lcd.print("Rel Intensity");
}

void loop () {
  for (int i = 0; i<50; i++){
    int readings = analogRead(0);
    ave += readings;
  }
  ave /= 50.0;
  sensor = map(int(ave), 0, 1023, 0, 255);
  sensor = constrain(int(ave), 0, 255);
  Serial.println(sensor); 
  vlib.lcdCmd(0xC0); // Prints in the first line
  vlib.lcdPrint(sensor);
  vlib.lcdPrint("    ");
//  lcd.setCursor(0,1);
//  lcd.print("   ");
//  lcd.setCursor(0,1);
//  lcd.print(sensor);
  delay(1000);
  ave = 0;
}




