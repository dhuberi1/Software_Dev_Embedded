// #include <Arduino.h>

// // Define pin for temperature sensor
// const int TEMP_SENSOR_PIN = A0;

// /*
// Variables: 
// latest_tamp_far: Latest temperature reading - in fareigheight. 
//                  Should be volatile since it can be updated w/in an ISR.
//                  Should always be read from memory 
// new_temp_available: Boolean flag to indicate if a new temp reading is available. 
//                     Can be modified inside an interrupt service routine, --> changes show in main loop 
// last_read_time:  Last timestamp when temperature was taken. Should be inside an interrupt? 
// interval:  Time interval between readings set from assignment. Const for now.
// */ 
// volatile float latest_temp_far = 0.0; 
// volatile bool new_temp_available = false;
// unsigned long last_read_time = 0;
// const unsigned long interval = 10000; // 10 seconds

// // ISR for timer
// void timerISR() {
//     // Set flag to indicate it's time to read temperature
//     new_temp_available = true;
// }

// // Initialize sensor
// void initSensor() {
//     // Configure temperature sensor pin and other settings
// }

// // Read raw temperature data
// int readRawTemperature() {
//     // Read analog value from sensor
//     return 0; 
// }

// // Convert raw temp to Fahrenheit
// float convertToFahrenheit(int rawValue) {
//     // Convert analog value to Fahrenheit
//     return 0.0; 
// }

// // Log temp over Serial
// void logTemperature(unsigned long timeStamp, float temperature) {
//     // Transmit time and temperature over Serial
// }

// // Storing here for initial thoughts - this will be in the .ino file 
// void setup() {
//     Serial.begin(9600);
//     initSensor();
    
//     // Set up timer interrupt for periodic readings
//     // Configure timer here and attach timerISR()
// }

// void loop() {
//     // Round Robin execution? 
//     if (new_temp_available) {
//         int rawTemp = readRawTemperature();
//         latest_temp_far = convertToFahrenheit(rawTemp);
//         logTemperature(millis(), latest_temp_far);
//         new_temp_available = false;
//     }
// }

