#include<Servo.h>
Servo myServo;
int pos=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A5,INPUT);
  Serial.begin(9600);
  myServo.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value=analogRead(A5);
  Serial.print("Value");
  Serial.println(value);
  if(value>500){
    for(pos=0;pos<=180;pos++){
      myServo.write(pos);
      delay(5);
    }
    for(pos=180;pos>=0;pos--){
      myServo.write(pos);
      delay(5);
    }
  }
  delay(2000);
}
