#include <Arduino_FreeRTOS.h>

// Global Variables
volatile float roll = 0;
volatile float pitch = 0;
volatile float yaw = 0;

//Tasks
TaskHandle_t loop_task;
TaskHandle_t imu_read_task;
TaskHandle_t serial_out_task;

void setup() {
  // Opens serial on 115200 baud rate 
  Serial.begin(115200);

  // Waits for the serial to be open
  while (!Serial) {

  }

  // Creates loop task
  // From: https://github.com/arduino/ArduinoCore-renesas/blob/main/libraries/Arduino_FreeRTOS/examples/FreeRTOS-Blink/FreeRTOS-Blink.ino
  auto const rc_loop = xTaskCreate
    (
      loop_thread_func,
      static_cast<const char*>("Loop Thread"),
      512 / 4,   /* usStackDepth in words */
      nullptr,   /* pvParameters */
      1,         /* uxPriority */
      &loop_task /* pxCreatedTask */
    );

  if (rc_loop != pdPASS) {
    Serial.println("Failed to create 'loop' thread");
    return;
  }

  // Create imu_read task
  auto const rc_imu_read = xTaskCreate
    (
      imu_read_thread_func,
      static_cast<const char*>("IMU Read Thread"),
      512 / 4,   /* usStackDepth in words */
      nullptr,   /* pvParameters */
      1,         /* uxPriority */
      &imu_read_task /* pxCreatedTask */
    );

  if (rc_imu_read != pdPASS) {
    Serial.println("Failed to create 'imu_read' thread");
    return;
  }

  // Create serial_out task
  auto const rc_serial_out = xTaskCreate
    (
      serial_out_thread_func,
      static_cast<const char*>("Serial Out Thread"),
      512 / 4,   /* usStackDepth in words */
      nullptr,   /* pvParameters */
      1,         /* uxPriority */
      &serial_out_task /* pxCreatedTask */
    );

  if (rc_serial_out != pdPASS) {
    Serial.println("Failed to create 'serial_out' thread");
    return;
  }

  // Starts the task scheduler
  Serial.println("Starting scheduler ...");
  vTaskStartScheduler();

  for( ;; );
}

// Loop task function
void loop_thread_func(void *pvParameters)
{
  for(;;)
  {
    loop();
    taskYIELD();
  }
}

void loop() {
  Serial.println(millis());
  vTaskDelay(configTICK_RATE_HZ/4);
}

// IMU Read task function
void imu_read_thread_func(void *pvParameters)
{
  for(;;)
  {
    roll += 1;
    pitch += 2;
    yaw += 3;

    vTaskDelay(configTICK_RATE_HZ);
  }
}

// Serial Out task function
void serial_out_thread_func(void *pvParameters)
{
  for(;;)
  {
    Serial.print(roll);
    Serial.print(",");
    Serial.print(pitch);
    Serial.print(",");
    Serial.println(yaw);

    vTaskDelay(configTICK_RATE_HZ);
  }
}