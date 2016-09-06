//#include <vLib.h>
//#include <stdlib.h>
#include <LiquidCrystal.h>
#include <math.h>
//vLib vlib;

LiquidCrystal lcd(7, 8, 9, 2, 4, 6);
float v1=0;
float v2=0;
float v3=0;
float v4=0;
float vout, R2, buff;
float R1 = 9450;  // resistor value of R1 in the voltage divider circuit for the voltmeter 
float Rs = 1;  // burden resistor for the ammeter = 1 ohm
float vin = 5;  // 5 volts from Arduino
int data = 0;
int roffset = 0;
float i1;

 

void setup(){
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  Serial.begin(9600);
//  analogReference(INTERNAL);
//  vlib.lcdInitialize(9,8); // 9 - DATA; 8 - CLOCK
}

void loop(){
  //Connect voltmeter probes to A1 & A2 port
  //Connect Ohmmeter probe to A1 port
  //Connect ammeter probes to A3 & A4 port
  
  //Gets voltage data for 5 seconds, then the average of the data
  while (millis()%1000 != 0) {
    v1 = v1 + (analogRead(A0)*vin)/float(1024);  // v1 = higher potential side
    v2 = v2 + (analogRead(A1)*vin)/float(1024);  // v2 = lower potential side
    v3 = v3 + (analogRead(A2)*vin)/float(1024);
    v4 = v4 + (analogRead(A3)*vin)/float(1024);
    data++;  
  }
  
  v1 = v1/float(data);
  vout = v1;           // for the ohmmeter; vout = voltage across the measured resistor 
  v2 = v2/float(data);
  v3 = v3/float(data);
  v4 = v4/float(data);
  
  //Ohmmeter
  //Voltage division: Vout = Vin(R2/(R1+R2))
  buff = (vin/vout) - 1.00;
  R2 = -0.00000004*(R1/buff)*(R1/buff) + 0.999*(R1/buff) + 18.7278;
//  R2 = 0.9921*(R1/buff) + 66.392;
//  R2 = (R1/buff);
  Serial.println(R2,5);  

//  Serial.print(v1);Serial.print(", ");
//  Serial.println(v2);
//  Serial.print(v3, 5);Serial.print(", ");
//  Serial.println(v4, 5);
  
//  seriallcd();  // prints the units at the first line using vlib
  
  //Ohms
  
//  vlib.lcdCmd(0xC0); // Prints in the second line
//  vlib.lcdPrint(abs(int(R2)));
//  vlib.lcdPrint("  ");
  
  //Voltmeter
  //Potential difference between two points v1 & v2
  
//  vlib.lcdCmd(0xC6); // Prints in the second line
//  vlib.lcdPrint(v1-v2);  // voltage across
  
  //Amperes
  //Gets the potential differemce across the burden resistor Rs 
  //then divide it by the resistor value
  //to obtain the current through the circuit
  i1 = ((v3-v4)*float(1000))/float(Rs);
  Serial.println(i1,5);
//  int i = (1.1988*i1) - 0.0442;
  int i = 0.0032*pow(i1,2) + 0.7374*i1 + 7.2014;
//  int i = 0.000001*pow(i1,4) - 0.0003*pow(i1,3) + 0.0234*pow(i1,2) + 0.2496*i1 + 8.0405;
//  int i = round(i1);
  
//  vlib.lcdCmd(0xCC); // Prints in the second line
//  vlib.lcdPrint(int((v3-v4)*1000/Rs)); //milliamperes

  liqlcd();  // prints the units at the first line using LiquidCrystal
  
  lcd.setCursor(0,1); // Prints in the second line
  if (R2 >= 1000000) {
    lcd.print(float(((abs(R2)))/float(1000000)),2);
    lcd.print(" M");
  } else if (R2 >= 99999) {
    lcd.print(long(((abs(R2)))/float(1000)));
    lcd.print(" k ");
  } else if (R2 >= 1000) {
    lcd.print(float(((abs(R2)))/float(1000)),2);
    lcd.print("k ");
  } else {
    lcd.print(long(abs(R2)));
    lcd.print("     ");
  }
  lcd.setCursor(6,1); // Prints in the second line
  lcd.print(float(v1-v2),2);  // voltage across
  lcd.setCursor(12,1); // Prints in the second line
  lcd.print(i);
//  lcd.print(int(((v3-v4)*1000)/float(Rs)));  //milliamperes
  lcd.print("   ");
  v1=v2=v3=v4=data=0;
  //delay(500);  
}

//void seriallcd(){
//  vlib.lcdCmd(0x80); // Prints in the first line  
//  vlib.lcdPrint("OHM:");
//  vlib.lcdCmd(0x86); // Prints in the second line
//  vlib.lcdPrint("VOLT:");
//  vlib.lcdCmd(0x8C);
//  vlib.lcdPrint("mA:");
//}

void liqlcd(){
  lcd.setCursor(0,0); // Prints in the first line  
  lcd.print("OHM:");
  lcd.setCursor(6,0); // Prints in the second line
  lcd.print("VOLT:");
  lcd.setCursor(12,0);
  lcd.print("mA:");
}
