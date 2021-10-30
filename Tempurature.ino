int outputpin=0;

void setup(){
  Serial.begin(9600);
}
void loop(){
  int rowVoltage=analogRead(A0);
  float mv=(rowVoltage/1024.0)*5000;
  float c = mv/10;
  Serial.println(c);
  delay(1000);
}
