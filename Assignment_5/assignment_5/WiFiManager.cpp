#include "WiFiManager.h"
#include <ESP8266WiFi.h>

const String ssid = "FiOS-GMAL3"; //replace this with your WiFi network name
const String password = "chili62bear5020hex"; //replace this with your WiFi network password

void connectToWiFi() {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to my Wifi: ");

    unsigned long startMillisec = millis(); 
    while (WiFi.status() != WL_CONNECTED) {
        // I just picked 10 seconds but happy to change it to another number 
        if (millis() - startMillisec > 10000) { 
            Serial.println("Check wifi passowrd/wifi connection");
            return; 
        }
        // Still waiting ofr connection 
        delay(500); 
        Serial.print(".");
    }

    // Once broken out of while loop, we are connected 
    Serial.print("\nConnected to Wifi"); 
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); 

}