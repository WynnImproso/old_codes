/* Ping))) Sensor
  
   This sketch reads a PING))) ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
     
   The circuit:
    * +V connection of the PING))) attached to +5V
    * GND connection of the PING))) attached to ground
    * SIG connection of the PING))) attached to digital pin 7

   http://www.arduino.cc/en/Tutorial/Ping
   
   created 3 Nov 2008
   by David A. Mellis
   modified 30 Aug 2011
   by Tom Igoe
 
   This example code is in the public domain.

 */

#include <vLib.h>
vLib vlib;
// Initialize the library with the numbers of the interface pins

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 6;
  float duration = 0;
  float cm;
  float sample = 0;
  int i = 0;
  unsigned long time1,time2;
  float period;
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  vlib.lcdInitialize(9,8);
  vlib.lcdPrint("SIMPLE HARMONIC ");
  vlib.lcdCmd(0XC4);
  vlib.lcdPrint("MOTION");
  delay(2000);
  vlib.lcdClear();
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  

  // convert the time into a distance
  // inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  
  if ((sample>=duration)&&(i==1)&&((sample-duration)>50))//
  {
    time2 = time1;
    time1 = millis();
   // Serial.println(time1);
   //Serial.println(time2);
    period = time1 - time2;
    Serial.print("T=");
    Serial.print(period/1000);
    Serial.println("s");
    i=0;
    
    vlib.lcdCmd(0x80);
    vlib.lcdPrint("Period:");
    vlib.lcdCmd(0xC0);
    period = period/1000;
    vlib.lcdPrint(period);
    vlib.lcdPrint("s        ");    
  }
  
  if ((sample<=duration)&&(i==0)&&(duration-sample)>50)
  {
    i=1;
  }
  
  sample = duration;
  
  // convert the time into a distance
  //inches = microsecondsToInches(duration);
  //cm = microsecondsToCentimeters(duration);



}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

float microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (1.0*microseconds / 29.0) * 0.5;
}
