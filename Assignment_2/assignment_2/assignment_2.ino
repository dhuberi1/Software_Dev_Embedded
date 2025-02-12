#include "FspTimer.h"
#include "temp_sense.h"

// Timer
FspTimer temp_timer;

// Analog input pin
int temp_pin = A0;
int send_data_pin = 2;

// Refernce voltage (V)
float v_ref = 5;

// Rate of the timer interrupt (Hz)
float rate = 1;


// Stores temperture and time into arrays to later be sent over serial
float volatile tempF[1000];
unsigned long volatile msec[1000];
int idx = 0;

// Count for 10s delay
int count = 0;

// Flag for sending data
bool sendData = false;

// Debounce parameters for button
unsigned long debounceTime = 0;
unsigned long debounceDelay = 500;

// Temp_sense object
Temp_Sense temp = Temp_Sense(temp_pin, v_ref);

/*
temp_timer_callback

Callback function of temp_timer.
Runs readTemp() function.
*/
void temp_timer_callback(timer_callback_args_t __attribute((unused)) *p_args) {
  count++;

  // Timer callback is called every 1s, ensures data is recorded every 10s 
  // Arduino does not seem to be able to have timer interrupts at 0.1 hz natively
  if (count % 10 == 0) {
    if (idx < 1000) {
      tempF[idx] = temp.readTemp();
      msec[idx] = millis();

      idx++;

      // resets count
      count = 0;
    }
  }
}

/*
send_data_ISR

Send data button interrupt.
Sets sendData to true if button has been pressed. Includes debounce protection.
*/
void send_data_ISR() {
  if ((millis() - debounceTime) > debounceDelay) {
    sendData = true;
  }
}

/*
beginTimer
from: https://www.pschatzmann.ch/home/2023/07/01/under-the-hood-arduino-uno-r4-timers/

Function to set up the timer.
*/
bool beginTimer(float rate) {
  uint8_t timer_type = AGT_TIMER;
  int8_t t_index = FspTimer::get_available_timer(timer_type);

  if (t_index < 0) {
    t_index = FspTimer::get_available_timer(timer_type, true);
  }
  if (t_index < 0) {
    return false;
  }

  if (!temp_timer.begin(TIMER_MODE_PERIODIC, timer_type, t_index, rate, 0.0f, temp_timer_callback)) {
    return false;
  }

  if (!temp_timer.setup_overflow_irq()) {
    return false;
  }

  if (!temp_timer.open()) {
    return false;
  }

  if (!temp_timer.start()) {
    return false;
  }

  return true;
}

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets pin temp_pin to an input
  pinMode(temp_pin, INPUT);

  // Sets send_data_pin to a input pullup and attaches a falling edge interrupt to it.
  pinMode(send_data_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(send_data_pin), send_data_ISR, FALLING);

  // Setsup and begins timer
  beginTimer(rate);

  // Print a CSV Header 
  Serial.println("Time in ms (ms), Temp (F)");
  
}

void loop() {
  // Checks if sendData flag is true
  if (sendData == true){
    // Dumps collected data over serial
    for (int i = 0; i < sizeof(tempF); i++) {
      if (msec[i] != 0){
        Serial.print(msec[i]); 
        Serial.print(","); 
        Serial.println(tempF[i]);
      }
      else {
        break;
      }
    }

    // Resets sendData flag
    sendData = false;
  }
}
