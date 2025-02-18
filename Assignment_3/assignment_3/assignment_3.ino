#include <Servo.h>

// Servo object
Servo esc;
int servo_pin = 3;

// IR detector pin
int IR_pin = 2;
int throttle_pin = A0;

// Records number of times and the time when the prop blade passes between the IR sensors 
int count = 0;
int msec[1000];

void IR_detect() {
  if (count < sizeof(msec)) {
    msec[count] = millis();
    count++;
  }
}

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets pin IR_pin to an input and attaches a rising edge interrupt to it
  pinMode(IR_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(IR_pin), IR_detect, RISING);

  // Sets throttle_pin to input and attaches esc to servo_pin
  pinMode(throttle_pin, INPUT);
  esc.attach(servo_pin);
}

void loop() {
  //Serial.println(count);

  int throttle = analogRead(throttle_pin);
  throttle = map(throttle, 0, 1023, 0, 179);

  esc.write(throttle);
  Serial.println(throttle);
}
