#include<SoftwareSerial.h>
SoftwareSerial mySerial(5,6);
int buzzerpin=13;
int echopin=12;
int trigpin=11;
int ldr=A0;
int light_value=0;
int light_threshold=20;
int moist_pin=A1;
int moistvalue=0;
int moist_threshold=850;
int push=0;
int push_in=2;
bool flag=0;

void setup(){
  pinMode(buzzerpin,OUTPUT);
  pinMode(push_in,INPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  digitalWrite(buzzerpin,LOW);
}

void loop(){
  push=digitalRead(push_in);
  Serial.print("0 ");
  Serial.println(push);
  if(push==1){
    digitalWrite(buzzerpin,HIGH);
   delay(1000);
   digitalWrite(buzzerpin,LOW);
    EmergencyCall();
  }
  delay(30);
  moistvalue=analogRead(moist_pin);
  Serial.print("1 ");
  Serial.println(moistvalue);
  if(moistvalue<moist_threshold){
    for (int i=0;i<3;i++){
      
      digitalWrite(buzzerpin,HIGH);
      delay(300);
      digitalWrite(buzzerpin,LOW);
      delay(500);;
    }
  }
  light_value=analogRead(ldr);
  Serial.print("3 ");
  Serial.println(light_value);
  if(light_value<light_threshold && flag==0){
    flag=1;
    for(int i=0; i<2;i++){
      digitalWrite(buzzerpin,HIGH);
      delay(300);
      digitalWrite(buzzerpin,LOW);
      delay(500);
    }
  }
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  float duration=pulseIn(echopin,HIGH);
  float cm=duration/29/2;
 Serial.print("4 ");
  Serial.println(cm);
  if (cm<10){
    for(int i=0;i<4;i++){
      digitalWrite(buzzerpin,HIGH);
      delay(300);
      digitalWrite(buzzerpin,LOW);
      delay(500);
    }
  }
  delay(1000);
}
void EmergencyCall() 
{ 
    mySerial.println("AT+CMGF=1"); 
    delay(1000);
    mySerial.println("AT+CMGS=\"+918088175010\"\r");
    delay(1000); 
    mySerial.print("I am in danger now "); 
    delay(100); 
    mySerial.println((char)26);
    delay(1000);

    Serial.println("CALLING.........."); 
    mySerial.println("ATD+918088175010;");
    delay(20000); 
    mySerial.println("ATH");
}
