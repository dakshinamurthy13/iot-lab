int pinRed=13;
int pinYellow=10;
int pinGreen=6;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinRed,OUTPUT);
  pinMode(pinYellow,OUTPUT);
  pinMode(pinGreen,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinRed,HIGH);
  digitalWrite(pinYellow,LOW);
  digitalWrite(pinGreen,LOW);
  delay(1000);
  digitalWrite(pinRed,LOW);
  digitalWrite(pinYellow,HIGH);
  digitalWrite(pinGreen,LOW);
  delay(1000);
  digitalWrite(pinRed,LOW);
  digitalWrite(pinYellow,LOW);
  digitalWrite(pinGreen,HIGH);
  delay(1000);
}
