#include<SoftwareSerial.h>
SoftwareSerial wifi(2,3);
void setup() {
   pinMode(9, OUTPUT);
  Serial.begin(9600);
  wifi.begin(9600);
}
void loop() {
  if (Serial.available()) {
    while (Serial.available()) {
      wifi.write(Serial.read());
    }
  }
if (wifi.available()) {
    while (wifi.available()) {
      Serial.write(wifi.read());
    }
  }
} 

