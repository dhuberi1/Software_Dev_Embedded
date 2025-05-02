#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "IMUHandler.h"

// Instance for IMUHandler 
IMUHandler imuHandler; 

// Task handles 
TaskHandle_t imu_read_task;
TaskHandle_t i2c_out_task;

// Global Variables
float data[3];
float roll = 0;
float pitch = 0;
float yaw = 0;

void setup() {
  // Opens serial on 115200 baud rate 
  Serial.begin(115200);

  Wire.begin();

  // Waits for the serial to be open
  while (!Serial) {

  }

  if (!imuHandler.begin()) { 
    Serial.println("IMU init failed"); 
    while(1); 
  }

  // Create imu_read task
  if (xTaskCreate(imu_read_thread_func, static_cast<const char*>("IMU Read Thread"), 512 / 4, nullptr, 1, &imu_read_task) != pdPASS) {
    Serial.println("Failed to create 'imu_read' thread");
    return;
  }

  // Create i2c_out task
  if (xTaskCreate(i2c_out_thread_func, static_cast<const char*>("Serial Out Thread"),512 / 4, nullptr, 1, &i2c_out_task) != pdPASS) {
    Serial.println("Failed to create 'i2c_out' thread");
    return;    
  }

  // Start RTOS task scheduler
  Serial.println("Starting scheduler ...");
  vTaskStartScheduler();

  // You never will actually get here 
  for( ;; );
}

void loop() {
  // Don't need anything here since each individual task has its own vTaskDelay()
}

// IMU Read task function
void imu_read_thread_func(void *pvParameters) {
  for(;;) {
    // Update roll, pitch, yaw variables 
    imuHandler.update();
    vTaskDelay(configTICK_RATE_HZ);
  }
}

void i2c_out_thread_func(void *pvParameters)
{
  for(;;)
  {
    roll = imuHandler.getRoll();
    pitch = imuHandler.getPitch();
    yaw = imuHandler.getYaw();

    Serial.println(roll);
    Serial.println(pitch);
    Serial.println(yaw);

    Wire.beginTransmission(9); // transmit to device #9
    Wire.write((byte*) &roll, sizeof(float));
    Wire.write((byte*) &pitch, sizeof(float));
    Wire.write((byte*) &yaw, sizeof(float));
    Wire.endTransmission();    // stop transmitting

    vTaskDelay(configTICK_RATE_HZ);
  }
}