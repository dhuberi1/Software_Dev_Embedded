#include <Servo.h>
#include "FspTimer.h"
#include "tachmeter.h"

// Timer
FspTimer speed_timer;

// Servo object
Servo esc;
int servo_pin = 5;

// IR detector pin
int IR_pin = 2;
int throttle_pin = A0;

// Data out pin
int send_data_pin = 3;

// Flag for sending data
bool sendData = false;

// Rate of timer interrupt (Hz)
float rate = 20;

// Debounce parameters for button
unsigned long debounceTime = 0;
unsigned long debounceDelay = 500;

// Records number of times and the time when the prop blade passes between the IR sensors 
int count = 0;
int msec[1000];


// /*
// IR_detect_ISR

// Records time an obstruction is detected and iterates the count.
// */
// void IR_detect_ISR() {
//   if (count < sizeof(msec)) {
//     msec[count] = millis();
//     count++;
//   }
// }

/*
speed_timer_callback

Reads the analog value on throttle_pin and maps it to a valid PWM value.
Sends PWM signal to the ESC.
*/
void speed_timer_callback(timer_callback_args_t __attribute((unused)) *p_args) {
  int throttle = analogRead(throttle_pin);
  throttle = map(throttle, 0, 1023, 0, 179);

  esc.write(throttle);
}

/*
send_data_ISR

Send data button interrupt.
Sets sendData to true if button has been pressed. Includes debounce protection.
*/
void send_data_ISR() {
  if ((millis() - debounceTime) > debounceDelay) {
    sendData = true;
    // Adding 
    debounceTime = millis(); 
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

  if (!speed_timer.begin(TIMER_MODE_PERIODIC, timer_type, t_index, rate, 0.0f, speed_timer_callback)) {
    return false;
  }

  // Added - just combined these since they all return false 
  if (!speed_timer.setup_overflow_irq() || !speed_timer.open() || !speed_timer.start()) {
    return false;
  }

  // if (!speed_timer.open()) {
  //   return false;
  // }

  // if (!speed_timer.start()) {
  //   return false;
  // }

  return true;
}

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets pin IR_pin to an input and attaches a rising edge interrupt to it
  pinMode(IR_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(IR_pin), IR_detect_ISR, RISING);

  // Sets throttle_pin to input and attaches esc to servo_pin
  pinMode(throttle_pin, INPUT);
  esc.attach(servo_pin);

  // Sets send_data_pin to a input pullup and attaches a falling edge interrupt to it.
  pinMode(send_data_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(send_data_pin), send_data_ISR, FALLING);

  // Sets up and begins timer
  beginTimer(rate);
}

// void loop() {
//   //Serial.println(count);

//   // Checks if sendData flag is true
//   if (sendData == true){
//     // Dumps collected data over serial
//     for (int i = 0; i < sizeof(msec); i++) {
//       if (msec[i] != 0){
//         Serial.println(msec[i]);
//       }
//       else {
//         break;
//       }
//     }

//     // Resets sendData flag
//     sendData = false;
//   }
// }

void loop() {
    // If button was pressed, send RPM data - now that were including header file 
    if (sendData) {
        Serial.print("RPM: ");
        Serial.println(getRPM());
        sendData = false;
    }  
}