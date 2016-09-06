#include <LiquidCrystal.h>

int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
float a = 0;
float b = 0;
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);

void setup()
{
  Serial.begin(9600);          //  setup serial
  lcd.begin(16, 2);
}

void loop()
{
  val = analogRead(analogPin);    // read the input pin
  a = val/206.306306;
  b = ((37.482*a) - 104.48805); 
  lcd.setCursor(0, 0); 
  lcd.print("Voltage = ");
  lcd.print(a);
  lcd.print("V  ");
  lcd.setCursor(0, 1);
  lcd.print("Conductivity = ");
  lcd.print(b); 
  lcd.print("mS/cm");             // debug value
  delay(1000);
}

