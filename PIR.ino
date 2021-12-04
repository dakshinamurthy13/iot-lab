int calibrationTime=30;
long unsigned int lowIn;
long unsigned int pause=5000;
boolean lockLow=true;
boolean takeLowTime;

int pirPin=3;
int ledPin=10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pirPin,INPUT);
  pinMode(ledPin,OUTPUT);

  Serial.println("Caliberting sensor");
  for(int i=0;i<calibrationTime;i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Done");
  Serial.println("Sersor Active");
  delay(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pirPin)==HIGH){
    digitalWrite(ledPin,HIGH);
    if(lockLow){
      lockLow=false;
      Serial.println("Motion detected at");
      Serial.println(millis()/1000);
      delay(50);
    }
    takeLowTime=true;
  }
  if(digitalRead(pirPin)==LOW){
    if(takeLowTime){
      lowIn=millis();
      takeLowTime=false;
    }
    if(!lockLow&&millis()-lowIn>pause){
      digitalWrite(ledPin,LOW);
      lockLow=true;
      Serial.println("motion ended at");
      Serial.println(lowIn/1000);
      delay(50);
    }
  }
}
