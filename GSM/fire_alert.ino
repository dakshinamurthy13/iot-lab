#include <SoftwareSerial.h>
SoftwareSerialcell(2,3);
void setup() {
    cell.begin(9600);
    delay(500);
    Serial.begin(9600);
    pinMode(A0,INPUT);
}
void loop() {
    int val=analogRead(A0);
    Serial.println(val);
    delay(1000);
    if (val<50)
    {
        Serial.println("CALLING..........");
        cell.println("ATD+919742980606;");
        delay(10000);
        cell.println("ATH"); // Attention Hook Control
    }
}