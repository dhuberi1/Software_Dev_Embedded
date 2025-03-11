#include <ESP8266WiFi.h>
// Replace these with your WiFi network settings
const char* ssid = "wifi"; //replace this with your WiFi network name
const char* password = "password"; //replace this with your WiFi network password

const char* host = "api.openweathermap.org";

void setup() {
  // From "ESP8266 Wi-Fi tutorial and examples using the Arduino IDE.docx" on Canvas
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);
  Serial.print("Connecting to ");
  Serial.println(host);

  // From "esp8266weatherstationgettingstartedguide-20180911.pdf" on Canvas
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection Failed!");
    return;
  }

  // Create URI for the request
  String url = "/data/2.5/weather?lat=";
  String lat = "38.8536";
  String lon = "-77.2531";
  String apikey = "cea27c2467ab3cb397c3c49c8bfdadc6";

  url = url + lat + "&lon=" + lon + "&appid=" + apikey;

  Serial.print("Requesting URL: ");
  Serial.print(url);

  // Send request to server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                "Host: " + host + "\r\n" + 
                "Connection: close\r\n\r\n");

  unsigned long timeout = millis();

  while (client.available() == 0) {
    if (millis() -timeout > 5000) {
      Serial.println(">>> Client Timeout!");
      client.stop();
      return;
    }
  }

  // Read all lines from reply from server
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}