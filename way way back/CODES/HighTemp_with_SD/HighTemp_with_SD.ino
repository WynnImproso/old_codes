// Display temperature in LCD using LM35 temperature sensor
#include<LiquidCrystal.h>
#include <SD.h>
#include <string.h>

// Initialize the library with the numbers of the interface pins
long time;
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);
const int chipSelect = 10;

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
  if (!SD.begin(chipSelect)) {
      Serial.println("Card failed, or not present");
      // don't do anything more:
      return;}
    Serial.println("card initialized.");
    long time;
    float temp;
}

void loop() {
int sensorf, sensorf1, sensorf2,i;
int sensor[10];
int sensor1[5];
int sensor2[5];
float ave,ave1,ave2;

  lcd.setCursor(0,0);
  time = millis();
  time=time/1000;
  Serial.print(time);
  Serial.print("\t");
  
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

//take five (5) readings from A0 A1 and A2 and get average for data processing  
for (i=0; i<10 ; i++){

  sensor[i] = analogRead(0); 
  sensor1[i] = analogRead(1); 
  sensor2[i] = analogRead(2);  
}
 sensorf = sensor[0] + sensor[1] + sensor[2] +sensor[3] + sensor[4]+sensor[5] + sensor[6] + sensor[7] +sensor[8] + sensor[9];
 ave = sensorf/10;
 sensorf1 = sensor1[0] + sensor1[1] + sensor1[2] +sensor1[3] + sensor1[4];
 ave1 = sensorf1/5;
 sensorf2 = sensor2[0] + sensor2[1] + sensor2[2] +sensor2[3] + sensor2[4];
 ave2 = sensorf2/5;  

  int temp = ((((ave * 5 )/1024)-0.881)*100)-0.6; // Convert to C
  lcd.print("t1:");
  lcd.print(temp);
  lcd.print("C  ");
  lcd.setCursor(9,0);
  int temp1 = ((((ave1 * 5 )/1024)-0.881)*100)-0.6;
  lcd.print("t2:");
  lcd.print(temp1);
  lcd.print("C  ");
  lcd.setCursor(0,1);
  int temp2 = ((((ave2 * 5 )/1024)-0.881)*100)-0.6;
  lcd.print("t3:");
  lcd.print(temp2);
  lcd.print("C  ");
  
  /*
  int temp1 = ave1 * 0.09765625; // Convert to C
  Serial.print("temp2: ");
  Serial.println(temp1);
  int temp2 = ave2 * 0.09765625; // Convert to C
  Serial.print("temp3: ");
  Serial.println(temp2);
  Serial.println(" ");*/
   String dataString = "";
  // if the file is available, write to it:

  char as[20];
  floatToString(as, temp1, 3, 3);
  dataString+= time;
    dataString+=",";
    dataString+= as;

    if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.csv");
  } 

  delay(1000);
}

char * floatToString(char * outstr, double val, byte precision, byte widthp){
  char temp[16]; //increase this if you need more digits than 15
  byte i;

  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");  //print "-" sign
    val *= -1;
  }

  if( precision == 0) {
    strcat(outstr, ltoa(round(val),temp,10));  //prints the int part
  }
  else {
    unsigned long frac, mult = 1;
    byte padding = precision-1;
    
    while (precision--)
      mult *= 10;

    val += 0.5/(float)mult;      // compute rounding factor
    
    strcat(outstr, ltoa(floor(val),temp,10));  //prints the integer part without rounding
    strcat(outstr, ".\0"); // print the decimal point

    frac = (val - floor(val)) * mult;

    unsigned long frac1 = frac;

    while(frac1 /= 10) 
      padding--;

    while(padding--) 
      strcat(outstr,"0\0");    // print padding zeros

    strcat(outstr,ltoa(frac,temp,10));  // print fraction part
  }

  // generate width space padding 
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);

    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }

  return outstr;
}
