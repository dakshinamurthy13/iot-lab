#define WIFISSID "SKS Cottage" // WIFI Username
#define WIFIPASS "kayar123" // WIFI Password
#define SERVERIP "api.thingspeak.com"// Server to post the update. "data.sparkfun.com"
#define POSTURL “POST /input/QGyLQKYb71F2Q1qMqQER?private_key=JqyBXeWg9ViqeBy9yevR&temperature=" 
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
 
void connectToWIFI() {
    String cwjapCmd = "AT+CWJAP=\"";
    cwjapCmd+=WIFISSID; 
    cwjapCmd+="\",\""; 
    cwjapCmd+=WIFIPASS; 
    cwjapCmd+="\"";
    sendToESP8266AndWaitForResponse (cwjapCmd.c_str(), "OK", true, 50);
}
 
void connectToServer() {
    String cipstartCmd = "AT+CIPSTART=\"TCP\",\"";
    cipstartCmd += SERVERIP; 
    cipstartCmd += "\",80";
    sendToESP8266AndWaitForResponse (cipstartCmd.c_str(), "Linked", true, 10);
}
 
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    
    // Setup Wifi as STA and connect to AP
    sendToESP8266AndWaitForResponse ("AT+CWMODE=1", "", false, 5);
    connectToWIFI();
    sendToESP8266AndWaitForResponse ("AT+CIPMUX=0", "OK", false, 50);
}
 
// the loop function runs over and over again forever
void loop() {
    char cmd[200],cipsend[100];

    int rawvoltage= analogRead(A0);
    float millivolts= (rawvoltage/1024.0) * 5000;
    float temp= millivolts/10; //celcius
    
    connectToServer();
    sprintf (cmd, "%s%d.%04d HTTP/1.0\r\n\r\n Host: %s\r\n\r\n",POSTURL, (int)temp,(int)trunc((temp-(int)temp)*10000),SERVERIP); 
    sprintf (cipsend, "AT+CIPSEND=%d",strlen(cmd));
    
    sendToESP8266AndWaitForResponse (cipsend, ">", true, 10);
    sendToESP8266AndWaitForResponse (cmd, "", false, 10);
    delay(10000); 
}
