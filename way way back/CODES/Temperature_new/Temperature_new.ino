// Display temperature in LCD using LM35 temperature sensor
#include<LiquidCrystal.h>
// Initialize the library with the numbers of the interface pins
#include <vLib.h>
vLib vlib;
unsigned long time;
//LiquidCrystal lcd(7, 8, 9, 2, 4, 6);

void setup() {
Serial.begin(9600);
//lcd.begin(16,2);
vlib.lcdInitialize(9,8);
}

void loop() {
int sensorf, sensorf1, sensorf2,i;
int sensor[5];
int sensor1[5];
int sensor2[5];
double ave,ave1,ave2;

  //lcd.setCursor(0,0);
  time = millis();
  time=time/1000;
  Serial.println(time);

//take five (5) readings from A0 A1 and A2 and get average for data processing  
for (i=0; i<5 ; i++){

  sensor[i] = analogRead(0); 
  sensor1[i] = analogRead(1); 
  sensor2[i] = analogRead(2);  
}
 sensorf = sensor[0] + sensor[1] + sensor[2] +sensor[3] + sensor[4];
 ave = sensorf/5;
 sensorf1 = sensor1[0] + sensor1[1] + sensor1[2] +sensor1[3] + sensor1[4];
 ave1 = sensorf1/5;
 sensorf2 = sensor2[0] + sensor2[1] + sensor2[2] +sensor2[3] + sensor2[4];
 ave2 = sensorf2/5;  

//  int temp = ave * 0.09765625; // Convert to C
  double temp = (ave * 5 * 100)/1024;
//  lcd.print("temp: ");
//  lcd.print(temp);
  Serial.print(temp);
  Serial.print("\t");
//  int temp1 = ave1;
  float temp1 = ((((ave1 * 5 )/1024)-0.881)*100)-0.6;
  Serial.println(temp1);
//  lcd.print("temp: ");
//  lcd.print(temp1);
  vlib.lcdPrint("temp: ");
  char cms[20];
 floatToString(cms,temp1, 1, 3);
  vlib.lcdPrint(cms);
  vlib.lcdPrint(" C     ");
  delay(1000); 

}


char * floatToString(char * outstr, double val, byte precision, byte widthp) {
  char temp[16]; //increase this if you need more digits than 15
  byte i;

  temp[0] = '\0';
  outstr[0] = '\0';

  if (val < 0.0) {
    strcpy(outstr, "-\0"); //print "-" sign
    val *= -1;
  }

  if ( precision == 0) {
    strcat(outstr, ltoa(round(val), temp, 10)); //prints the int part
  }
  else {
    unsigned long frac, mult = 1;
    byte padding = precision - 1;

    while (precision--)
      mult *= 10;

    val += 0.5 / (float)mult;    // compute rounding factor

    strcat(outstr, ltoa(floor(val), temp, 10)); //prints the integer part without rounding
    strcat(outstr, ".\0"); // print the decimal point

    frac = (val - floor(val)) * mult;

    unsigned long frac1 = frac;

    while (frac1 /= 10)
      padding--;

    while (padding--)
      strcat(outstr, "0\0");   // print padding zeros

    strcat(outstr, ltoa(frac, temp, 10)); // print fraction part
  }

  // generate width space padding
  if ((widthp != 0) && (widthp >= strlen(outstr))) {
    byte J = 0;
    J = widthp - strlen(outstr);

    for (i = 0; i < J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp, outstr);
    strcpy(outstr, temp);
  }

  return outstr;
}
