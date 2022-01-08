/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == MASTER CODE ==
 */

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

#define ledPin 9
int state = 0;
String message;
int potValue = 0;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
   Serial.begin(9600);
 // Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}


void loop() {
 if(BTSerial.available() > 0){ // Checks whether data is comming from the serial port



  
 
    
    
    
    message = BTSerial.readString(); // Reads the data from the serial port
    if(message.indexOf("SWITCH ON")>=0)
    {
     digitalWrite(ledPin, HIGH); // LED ON
    }
    else if(message.indexOf("SWITCH OFF")>=0)
    {
      digitalWrite(ledPin, LOW); // LED OFF
    }
    else
    {
      Serial.println("Noting to do");
    }
  //Serial.print(state);
  delay(100);
    
 }
 // Controlling the LED
 /*if (state == '1') {
  digitalWrite(ledPin, HIGH); // LED ON
  state = 0;
 }
 else if (state == '0') {
  digitalWrite(ledPin, LOW); // LED ON
  state = 0;
 }*/
 // Reading the potentiometer
 potValue = analogRead(A0);
 int potValueMapped = map(potValue, 0, 1023, 0, 255);
 BTSerial.write(potValueMapped); // Sends potValue to servo motor
 delay(10);
}
