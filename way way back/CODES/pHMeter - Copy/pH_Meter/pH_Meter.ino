  
//  pH Sensor Program
//  Reads pH data from pHSensor connected
//  serially to pin 3 and 5
//revised by
//Nelio C. Altoveros and Hazel Joyce M. Ramirez
//March 12, 2014
  
// The circuit: 
// * RX is digital pin 3 (connect to TX of other device)
// * TX is digital pin 5 (connect to RX of other device)
 
 
//  The LCD circuit:
// * LCD RS pin to digital pin 7
// * LCD Enable pin to digital pin 8
// * LCD D4 pin to digital pin 9
// * LCD D5 pin to digital pin 2
// * LCD D6 pin to digital pin 4
// * LCD D7 pin to digital pin 6
// * LCD R/W pin to ground
// * 10K resistor:
// *   ends to +5V and ground
// *   wiper (center) to LCD VO pin (pin 4)

// The SDCard circuit:
// * SD card attached to SPI bus as follows:
// ** CS - pin 10 - pin 4 is used by LCD
// ** MOSI - pin 11
// ** MISO - pin 12
// ** SCK - pin 13 (CLK)

//This pH code has intentionally has been written to be overly lengthy and includes unnecessary steps. 
//Many parts of this code can be truncated. This code was written to be easy to understand.
//Code efficiency was not considered. Modify this code as you see fit.    
//This code will output data to the Arduino serial monitor. Type commands into the Arduino serial monitor to control the pH circuit.
//set the var Arduino_only to equal 1 to watch the Arduino take over control of the pH circuit.



#include <SPI.h>
#include <SD.h>
#include <stdio.h>
#include<LiquidCrystal.h>

#include <SoftwareSerial.h>      //we have to include the SoftwareSerial library, or else we can't use it.  
#define rx 3                     //define what pin rx is going to be.
#define tx 5                     //define what pin Tx is going to be.

SoftwareSerial myserial(rx, tx); //define how the soft serial port is going to work. 

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 2, 4, 6);

const int chipSelect = 10;    // SDCard Chip Select ***** pin 4 is used by LCD
long ttime=0;
String dataString = "";
int suffix=1;
int firstrun=true;
char fname[15]="PH",filename[15]="PH001.TXT";

byte arduino_only=1;               //if you would like to operate the pH Circuit with the Arduino only
                                   // 0 - send comd using serial monitor
                                   // 1 - Arduino control
                                   // The data will still come out on the serial monitor.  
char ph_data[20];                  //we make a 20 byte character array to hold incoming data from the pH. 
char computerdata[20];             //we make a 20 byte character array to hold incoming data from a pc/mac/other. 
byte received_from_computer=0;     //we need to know how many characters have been received.                                 
byte received_from_sensor=0;       //we need to know how many characters have been received.
byte startup=0;                    //used to make sure the Arduino takes over control of the pH Circuit properly.
float pH=0.0;                      //used to hold a floating point number that is the pH. 
byte string_received=0;            //used to identify when we have received a string from the pH circuit.


void setup()
{
     pinMode(10, OUTPUT);
     Serial.begin(38400);         //enable the hardware serial port
     myserial.begin(38400);       //enable the software serial port
     initSDCard();
     initLcdDisplay();
     Serial.println("pH Meter");
     Serial.println("Time\tpH\tLevel");
     Serial.println("(ms)");
     
          
     //Uncomment to calibrate
     //s_cal();    //Calibrate to pH 7
     //f_cal();    //Calibrate to pH 4
     //t_cal();    //Calibrate to pH 10
}
  
void initSDCard()
{
  Serial.print("");
  Serial.println("phMeter Experiment");
  Serial.println("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
   if (!SD.begin(chipSelect)) {
     Serial.println("Card failed, or not present");
     // don't do anything more:
   }
   else {
   Serial.println("Card initialized.");
   }
   delay(2000);
}

void initLcdDisplay()
{
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("pH Meter");
  lcd.setCursor(0,1);
  lcd.print("Experiment"); 
}

void lcdDisplayData()
{
  lcd.setCursor(0,0);
  lcd.print("T(ms): ");
  lcd.setCursor(7,0);
  lcd.print(ttime);
  lcd.setCursor(0,1);
  lcd.print("pH:     ");
  lcd.setCursor(7,1);
  lcd.print(pH,2);
}

void labelData()
{
  while (SD.exists(filename)) {   
      Serial.print(filename);
      Serial.println(" exists");
      snprintf(filename, 12, "%s%03d.TXT", fname,++suffix);
  }
  Serial.print("Saving data to ");
  Serial.println(filename);
  File dataFile = SD.open(filename, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print("TIME");
    dataFile.print('\t');
    dataFile.println("pH");
    dataFile.println("(ms)");   
    dataFile.close();
  }
    //if the file isn't open, pop up an error:
  else {
    Serial.print("Error opening ");
    Serial.println(filename);
  } 
}


void logData(){
  File dataFile = SD.open(filename, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    
    dataFile.println(dataString);
    dataFile.close();
  }  
}   

 
 
void serialEvent()
{    
  //this interrupt will trigger when the data coming from the serial monitor(pc/mac/other) is received.    
  if(arduino_only!=1)
  { 
    //if Arduino_only does not equal 1 this function will be bypassed.  
    received_from_computer=Serial.readBytesUntil(13,computerdata,20); //we read the data sent from the serial monitor(pc/mac/other) until we see a <CR>. We also count how many characters have been received.      
    computerdata[received_from_computer]=0; //we add a 0 to the spot in the array just after the last character we received.. This will stop us from transmitting incorrect data that may have been left in the buffer. 
    myserial.print(computerdata);           //we transmit the data received from the serial monitor(pc/mac/other) through the soft serial port to the pH Circuit. 
    myserial.print('\r');                   //all data sent to the pH Circuit must end with a <CR>.  
  }    
}
 
 
  

void loop()
{ 
  long start=0;
  firstrun=true;
  labelData();
  start=millis();
  while(1) {
  if(myserial.available() > 0)
  {  //if we see that the pH Circuit has sent a character.
     received_from_sensor=myserial.readBytesUntil(13,ph_data,20); //we read the data sent from pH Circuit until we see a <CR>. We also count how many character have been received.  
     ph_data[received_from_sensor]=0;  //we add a 0 to the spot in the array just after the last character we received. This will stop us from transmitting incorrect data that may have been left in the buffer. 
     string_received=1;                //a flag used when the Arduino is controlling the pH Circuit to let us know that a complete string has been received.
     pH=atof(ph_data);
     ttime= (millis()-start);
     if (firstrun) {
       start=ttime;
       ttime=0;
       firstrun=false;
     }
     
     Serial.print(ttime);
     Serial.print("\t");
     Serial.print(ph_data);          //lets transmit that data received from the pH Circuit to the serial monitor.
     dataString=String(ttime)+"\t"+ph_data;
  }    
  
  if(arduino_only==1)
    {Arduino_Control();
  } //If the var arduino_only is set to one we will call this function. Letting the Arduino take over control of the pH Circuit    
  else Serial.println("");
  logData();
  lcdDisplayData();
 }
} 
  
  
  
  
void Arduino_Control()
{
  if(startup==0)
  {                
    //if the Arduino just booted up, we need to set some things up first.   
    myserial.print("e\r");     //take the pH Circuit out of continues mode. 
    delay(50);                 //on start up sometimes the first command is missed. 
    myserial.print("e\r");     //so, let’s send it twice.
    delay(50);                 //a short delay after the pH Circuit was taken out of continues mode is used to make sure we don’t over load it with commands.
    startup=1;                 //startup is completed, let's not do this again during normal operation. 
   }
      
  delay(800);                         //we will take a reading ever 800ms. You can make this much longer or shorter if you like.
  myserial.print("R\r");             //send it the command to take a single reading.
   if(string_received==1)
   { 
     //did we get data back from the ph Circuit?
     if (atof(ph_data)==0.0) {
       Serial.println("");
     } else
     {
     pH=atof(ph_data);                //many people ask us "how do I convert a sting into a float?" This is how...
     if(pH>=7.5)
       {
         Serial.println("\thigh\r");
       } //This is the proof that it has been converted into a float.
     if(pH<7.5)
       {
         Serial.println("\tlow\r");
       }   //This is the proof that it has been converted into a float
     }
     string_received=0;
   }             //reset the string received flag.
}  
 


//here are some functions you might find useful
//these functions are not enabled

void s_cal(){               //calibrate to a pH of 7
  myserial.print("s\r");}   //send the "s" command to calibrate to a pH of 7.00


void f_cal(){               //calibrate to a pH of 4 
  myserial.print("f\r");}   //send the "f" command to calibrate to a pH of 4.00 


void t_cal(){               //calibrate to a pH of 10.00
  myserial.print("t\r");}   //send the "t" command to calibrate to a pH of 10.00  


void phFactoryDefault(){    //factory defaults the pH circuit
  myserial.print("X\r");}   //send the "X" command to factory reset the device 


void read_info(){           //get device info
    myserial.print("I\r");} //send the "I" command to query the information


void phSetLEDs(byte enabled) //turn the LEDs on or off
{
  if(enabled)                //if enabled is > 0 
    myserial.print("L1\r");  //the LED's will turn ON 
  else                       //if enabled is 0        
    myserial.print("L0\r");  //the LED's will turn OFF
}




   


  

