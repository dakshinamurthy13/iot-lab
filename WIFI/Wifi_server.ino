#include "SoftwareSerial.h"

#define WIFISSID "Name"      // WIFI Username
#define WIFIPASS "password"         // WIFI Password

SoftwareSerial Serial1(2,3);
void sendToESP8266AndWaitForResponse (const char *cmd, const char *resp, bool waitForResponse, int duration) {
  String bytes;
  Serial.print ("CMD: "); 
  Serial.println(cmd);
  do {
    Serial.print(".");
    Serial1.println (cmd);
    delay(duration);
    bytes = Serial1.readString();
  } while ( (waitForResponse) && (bytes.indexOf(resp)<0));
  Serial.print ("RESPONSE: ");
  Serial.print (bytes.c_str());
  Serial.println("\n------------------------------");
}

void setupAP() {
  String cwsapCmd = "AT+CWSAP=\"";
  cwsapCmd+=WIFISSID;  
  cwsapCmd+="\",\""; 
  cwsapCmd+=WIFIPASS; 
  cwsapCmd+="\",8,0";
  sendToESP8266AndWaitForResponse (cwsapCmd.c_str(), "OK", true, 50);
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(11,OUTPUT);

  // Setup Wifi as AP
  sendToESP8266AndWaitForResponse ("AT+CWMODE=2", "", false, 5);
  setupAP();
  sendToESP8266AndWaitForResponse ("AT+CIPMUX=1", "OK", false, 50);
  sendToESP8266AndWaitForResponse ("AT+CIPSERVER=1", "OK", false, 50);
}

// the loop function runs over and over again forever
void loop() {
  if(Serial1.available())
  {
   String message = Serial1.readString();
   Serial.println (message);
    if(message.indexOf("LED ON")>0)
    {
      digitalWrite(11,HIGH);
    }
    else if(message.indexOf("LED OFF")>0)
    {
      digitalWrite(11,LOW);
    }
    else
    {
      Serial.println ("Nothing to do...");
    }
  
  }
  
}
