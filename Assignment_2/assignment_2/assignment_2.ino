#include "FspTimer.h"
#include "temp_sense.h"

// Timer
FspTimer temp_timer;

// Analog input pin
int temp_pin = A0;

// Refernce voltage (V)
float v_ref = 5;

// Rate of the timer interrupt (Hz)
float rate = 0.1;

float f;

// Temp_sense object
Temp_Sense temp = Temp_Sense(temp_pin, v_ref, rate);

/*
temp_timer_callback

Callback function of temp_timer.
Runs readTemp() function.
*/
void temp_timer_callback(timer_callback_args_t __attribute((unused)) *p_args) {
  f = temp.readTemp();
}

/*
beginTimer
from: https://www.pschatzmann.ch/home/2023/07/01/under-the-hood-arduino-uno-r4-timers/

Function to set up the timer.
*/
bool beginTimer(float rate) {
  uint8_t timer_type = GPT_TIMER;
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

  // Sets pin A0 to an input
  pinMode(temp_pin, INPUT);

  // Setsup and begins timer
  beginTimer(rate);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(f);
}
