#include "WebServer.h"
#include "WeatherClient.h"
#include <ESP8266WiFi.h>

// Set webserver port to 80
WiFiServer server(80);

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Variable to store the HTTP request
String header;

// Opens the server
void openServer() {
    server.begin();
}

// From https://randomnerdtutorials.com/esp8266-web-server/
// Handles HTTP requests from clients and sends them HTML Webpage
void hostWebServer() {

    // Listen for incoming clients
    WiFiClient client = server.available();

    // If a new client connects
    if (client) {
      Serial.println("New Client.");

      // Make a String to hold incoming data from the client
      String currentLine = "";

      // Timeout variables
      currentTime = millis();
      previousTime = currentTime;

      // Loop while the client's connected
      while (client.connected() && currentTime - previousTime <= timeoutTime) {
        currentTime = millis();

        // If there's bytes to read from the client     
        if (client.available()) {         
          char c = client.read();
          Serial.write(c);
          header += c;

          // if the byte is a newline character
          if (c == '\n') {

            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) {

              // Actually get the weather data 
              String weatherData = fetchWeatherData();

              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();
              
              // Display the HTML web page
              client.println("<!DOCTYPE html><html>");
              client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              client.println("<link rel=\"icon\" href=\"data:,\">");

              client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style></head>");
              // Put the weather data on the html page 
              client.println("<body><h1>ESP8266 Web Server</h1>");
              client.println("<h2>Current Weather: </h2>");
              client.println("<p>" + weatherData + "</p>");
              client.println("</body></html>");
              
              // The HTTP response ends with another blank line
              client.println();

              // Break out of the while loop
              break;
            } 
            else {
              // if you got a newline, then clear currentLine
              currentLine = "";
            }
          }
          // if you got anything else but a carriage return character,
          else if (c != '\r') {  
            // add it to the end of the currentLine
            currentLine += c;
          }
        }
      }
      // Clear the header variable
      header = "";

      // Close the connection
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");
    }
}
