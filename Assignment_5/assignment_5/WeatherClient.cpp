#include "WeatherClient.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

String fetchWeatherData() {
    WiFiClient client; 
    String host = "api.openweathermap.org";
    String lat = "38.8536";
    String lon = "-77.2531";
    String apikey = "cea27c2467ab3cb397c3c49c8bfdadc6";
    String url = "/data/2.5/weather?lat=" + lat + "&lon=" + lon + "&appid=" + apikey;

    // Connect to OpenWeatherMap server with standard client.connect()
    if (client.connect(host.c_str(), 80)) {
        // ACtual HTTP GET request
        client.println("GET " + url + " HTTP/1.1");
        client.println("Host: " + host);
        client.println("Connection: close");
        client.println();

        while (!client.available()) {
            delay(10);
        }

        // Read now response (HTTP response is be split into header/body)
        String response = "";
        while (client.available()) {
            response += client.readString();
        }

        client.stop();  // Close the connection

        // Parse the response to extract weather data
        return parseJson(response);
    } else {
        // If connection fails
        Serial.println("Connection to server failed");
        return "Connection failed";
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

    // Extract temperature and humidity
    float temperature = doc["main"]["temp"] - 273.15;
    int humidity = doc["main"]["humidity"];

    // Build the weather information string
    String weatherInfo = "Temp: ";
    weatherInfo += String(temperature, 2);
    weatherInfo += ", Humidity: ";
    weatherInfo += String(humidity);

    return weatherInfo;
}
