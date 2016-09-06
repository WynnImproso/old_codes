#include <vLib.h>
vLib vlib;
int counter = 0;

void setup(){
  Serial.begin(9600);
  vlib.lcdInitialize(9,8);
}

void loop(){
  double x[5];
  int i;
  for (i=0; i<5; i++){
    x[i] = analogRead(A0);
    x[i] = (x[i]*5)/1024;
    delay(1000);
  }
  float xave = ((x[0]+x[1]+x[2]+x[3]+x[4])/5);
  float conductivity = 39.715*(exp(1.859*xave));
  Serial.print(counter);
  Serial.print("\t \t");
  Serial.println(conductivity, 5);
  vlib.lcdCmd(0x80); // Prints in the first line
  vlib.lcdPrint("cond:");  
  vlib.lcdCmd(0xC0); // Prints in the second line  
  
  vlib.lcdPrint(conductivity); // Sensor 1
  vlib.lcdPrint("uS/cm     ");
  vlib.lcdCmd(0x8D);
  vlib.lcdPrint(counter);
  counter = counter + 5;  
}  
