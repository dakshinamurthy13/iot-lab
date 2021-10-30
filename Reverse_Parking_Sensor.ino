int trigPin=2;
int echoPin=4;
int buzzerIn=9;

void setup(){
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(buzzerIn,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  float duration=pulseIn(echoPin,HIGH);
  float cm=duration/29/2;
  Serial.print("Disance in cm=");
  Serial.println(cm);
  if(cm>10){
    digitalWrite(buzzerIn,LOW);
  }else{
    digitalWrite(buzzerIn,HIGH);
  }
  delay(1000);
}
