#include <Servo.h>
#define button 8

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

Servo myServo;
int state = 20;
int buttonState = 0;
void setup() {
  pinMode(button, INPUT);
  myServo.attach(9);
  Serial.begin(9600);
 // Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}
void loop() {
 if(BTSerial.available() > 0){ // Checks whether data is comming from the serial port
    state = BTSerial.read(); // Reads the data from the serial port
 }
 // Controlling the servo motor
 myServo.write(state);
 delay(10);
 
 // Reading the button

 if(Serial.available())
  {
   String message = Serial.readString();
   Serial.println (message);
    BTSerial.write(message.c_str());
    
    
    /*if(message.indexOf("SWITCH ON")>=0)
    {
     BTSerial.write('1');
    }
    else if(message.indexOf("SWITCH OFF")>=0)
    {
      BTSerial.write('0');
    }
    else
    {
      Serial.println("Noting to do");
    }*/
  }


 


 
 /*buttonState = digitalRead(button);
 if (buttonState == HIGH) {
  //Serial.write('1');
   BTSerial.write('1'); // Sends '1' to the master to turn on LED
 }
 else {
  //Serial.write('0');
   BTSerial.write('0');
 }  */
}
