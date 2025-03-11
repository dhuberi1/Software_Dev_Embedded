#include <ESP8266WiFi.h>
#include "WiFiManager.h"
#include "WeatherClient.h"

void setup() {
  // From "ESP8266 Wi-Fi tutorial and examples using the Arduino IDE.docx" on Canvas
  delay(1000);
  Serial.begin(115200);
  // connect to Wifi 
  connectToWiFi(); 
}

void loop() {
  // Call OpenWeatherMap API for weather data 
  String weatherData = fetchWeatherData(); 
  Serial.println("Weather Data: " + weatherData);
  delay(5000);

}