#include <ESP8266TimerInterrupt.h>
#include <ESP8266_ISR_Timer.h>
#include <ESP8266_ISR_Timer.hpp>

#include <ESP8266WiFi.h>
#include "WiFiManager.h"
#include "WeatherClient.h"
#include "WebServer.h"

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

// Init ESP8266 only and only Timer 1
ESP8266Timer ITimer;

#define TIMER_FREQ_HZ        0.2

// Flag for querying OpenWeatherMap API for weather data
bool checkWeather = false;

// checkWeatherISR
// Sets checkWeather flag to true
void queryWeatherTimer() {
  checkWeather = true;
}

// Call OpenWeatherMap API for weather data
void queryWeather()
{
  String weatherData = fetchWeatherData();
  Serial.println("Weather Data: " + weatherData);
}

void setup() {
  // From "ESP8266 Wi-Fi tutorial and examples using the Arduino IDE.docx" on Canvas
  Serial.begin(115200);

  // Connect to Wifi 
  connectToWiFi();
  openServer();

  // Frequency in float Hz
  if (ITimer.attachInterrupt(TIMER_FREQ_HZ, queryWeatherTimer)) {
    Serial.println("Starting  ITimer OK, millis() = " + String(millis()));
  }
  else {
    Serial.println("Can't set ITimer. Select another freq. or timer");
  }
}

void loop() {

  //
  hostWebServer();
  
  // if checkWeather flag is true and if it is, queries OpenWeatherMap API
  if (checkWeather == true) {
    queryWeather();
    checkWeather = false;
  }
}