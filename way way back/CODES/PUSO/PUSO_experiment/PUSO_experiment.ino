//#include <SerialLCD.h>
//
//SerialLCD seriallcd(9,8);

int T1, T2;

float fave=0;
float Have=0;
float m1=0;
float m2=0;
int beat = 0;

void setup(){
  Serial.begin(9600);
//  seriallcd.lcdInit();
}

void loop() {
  m2 = millis()/1000;
  while (analogRead(0) >= 201); // 21 = 100 mVolts
  while (analogRead(0) <= 201);
  T1 = millis();
  while (analogRead(0) >= 201);
  while (analogRead(0) <= 201);
  T2 = millis();
  float Time = T2-T1;
  Time = Time/1000;
  float freq = 1/Time;
  float HeartRate = 60*freq;
//  Serial.println(T1);
//  Serial.println(T2);
//  Serial.println(Time);
  if(freq<=4 && freq>=0.5) {
    beat = beat+1;
    fave = fave+freq;
    Serial.print(freq);
    Serial.println(" BPS");
//    seriallcd.lcdPrintnum(freq);
//    seriallcd.lcdPrint(" BPS");
    Have = Have+HeartRate;
    Serial.print(HeartRate);
    Serial.println(" BPM");
//    seriallcd.lcdPrintnum(HeartRate);
//    seriallcd.lcdPrint(" BPM");
  }
// average beats per sec/minute  
  if ((m2-m1) >= 60) {
    Serial.print(fave/beat);
    Serial.println(" BPS (ave)");
    Serial.print(Have/beat);
    Serial.println(" BPM (ave)");
    beat = 0;
    fave = 0;
    Have = 0;
    m1 = m2;
  }   
  Serial.println(m2);
  delay(1000);
}

