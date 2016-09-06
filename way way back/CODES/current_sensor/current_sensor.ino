void setup(){
  Serial.begin(9600);
}

void loop(){
  double amp, ans;
  double ave = 0;
  int val;
for (int i=0; i<100;i++){  
  val = analogRead(A0);
  amp = val*0.048828125;
  ans = amp - 24.9;
  ave = ave + (ans/100);
  delay(5);
}
  Serial.println(val);
  Serial.println(ans);

  
/*  Serial.println(analogRead(A0));
   average = average + (0.026 * analogRead(A0) - 13.51) / 1000;
  Serial.println(average);   
  delay(1000);*/
}
