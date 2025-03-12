#ifndef WEATHER_CLIENT_H 
#define WEATHER_CLIENT_H 

#include <Arduino.h> 

String fetchWeatherData();
String parseJson(String payload);

#endif