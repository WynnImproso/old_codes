#include <vLib.h>
vLib vlib;
int counter = 6;
int T1,T2;
int t = 0;

//#include<LiquidCrystal.h>
//
//LiquidCrystal lcd(7,8,9,2,4,6);

void setup() {
  Serial.begin(9600);
//  lcd.begin(16,2);
  vlib.lcdInitialize(9,8);
}

void loop(){
  float ave;
//  t =((analogRead(A1)*100*5)/1024);
  

  
//  Serial.println(t); 
//  lcd.setCursor(0,0);
//  lcd.print("Temp:");
//  lcd.print(ave);
//  lcd.print("    "); 
  
  vlib.lcdCmd(0x80);
//  vlib.lcdPrint("Temp:");
//  vlib.lcdPrint(t);
//  vlib.lcdPrint("    ");

  while (analogRead(A0) >= 201); // 21 = 100 mVolts
  while (analogRead(A0) <= 201);
  T1 = millis();
  while (analogRead(A0) >= 201);
  while (analogRead(A0) <= 201);
  T2 = millis();
  float Time = T2-T1;
//  while (analogRead(A0) >= 201); // 21 = 100 mVolts
//  while (analogRead(A0) <= 201);
//  T1 = millis();
//  while (analogRead(A0) >= 201);
//  while (analogRead(A0) <= 201);
//  T2 = millis();
//  float Time1 = T2-T1;
//  while (analogRead(A0) >= 201); // 21 = 100 mVolts
//  while (analogRead(A0) <= 201);
//  T1 = millis();
//  while (analogRead(A0) >= 201);
//  while (analogRead(A0) <= 201);
//  T2 = millis();
//  float Time2 = T2-T1;

//  float Timeave = (Time+Time1+Time2)/3;
  Time = Time/1000;
  float freq = 1/Time;
  int HeartRate = 60*freq;

//  lcd.setCursor(0,1); // Prints in the first line
//  lcd.print("<3rate:"); 
  vlib.lcdPrint("<3rate:"); 
  vlib.lcdCmd(0xC0); // Prints in the first line
 
   
  
  if(freq<=4 && freq>=0.5) {
    Serial.print(freq);
    Serial.print("\t");
    Serial.println(HeartRate);

//    lcd.print(HeartRate); // Sensor 1
//    lcd.print("BPM              ");

    vlib.lcdPrint(HeartRate); // Sensor 1
    vlib.lcdPrint("BPM              ");
//    Serial.println(" BPM");
    
  }
  else {
//    lcd.print(" ");
    vlib.lcdPrint("                  ");  
  }
  
  while(counter > 0) {
    vlib.lcdCmd(0x8F);
    delay(1000);
    counter--;
    vlib.lcdPrint(counter);
  }
  counter = 6;

}
