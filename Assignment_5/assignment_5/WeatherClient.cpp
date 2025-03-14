#include "WeatherClient.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h> 

String fetchWeatherData() {
    // Create URI for the request
    HTTPClient http; 
    String host = "api.openweathermap.org";
    String lat = "38.8536";
    String lon = "-77.2531";
    String apikey = "cea27c2467ab3cb397c3c49c8bfdadc6";
    String url = "http://" + host + "/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + apikey + "&units=imperial";

    http.begin(url); 
    // Send actual GET request 
    int httpCode = http.GET(); 

    if (httpCode > 0) { 
        // Success 
        String payload = http.getString(); 
        Serial.println("HTTP Response success");

        // parse JSON 
        return parseJson(payload); 

    } else {
        Serial.print("Error when doing the HTTP request iwth error code: ");
        Serial.println(httpCode);
        return "HTTP Request Failed 404";
    }
}

String parseJson(String payload) {
    // Req. json document 
    StaticJsonDocument<200> doc; 
    DeserializationError error = deserializeJson(doc, payload); 

    if (error) {
        // Failed 
        Serial.print("Deserialization failed ): ");
        Serial.println(error.c_str()); 
        return ""; 
    } 
    
    // we want temp and humidity (i got it in Kelvin??)
    float temperature = float(doc["main"]["temp"]);
    int humidity = int(doc["main"]["humidity"]);

    // Build the weather information string
    String weatherInfo = "Temp: ";
    weatherInfo += String(temperature, 2);
    weatherInfo += " F, Humidity: ";
    weatherInfo += String(humidity);

    return weatherInfo;
}
