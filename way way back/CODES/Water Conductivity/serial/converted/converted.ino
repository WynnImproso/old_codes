int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read
float a = 0;
float b = 0;

void setup()
{
  pinMode (3, OUTPUT) ;
  Serial.begin(9600);          //  setup serial
  TCCR2B = 0x07;
  analogWrite(3,128);
}

void loop()
{
  val = analogRead(analogPin);    // read the input pin
  a = val/206.306306;
  b = ((37.482*a) - 104.48805);  
  Serial.print("Voltage = ");
  Serial.print(a);
  Serial.print("V  ");
  Serial.print("Conductivity = ");
  Serial.print(b); 
  Serial.println("mS/cm");             // debug value
  delay(1000);
}

