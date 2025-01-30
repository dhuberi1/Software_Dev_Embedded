#include "Morse.h"

// Digital Output Pin for LED
int led_pin = 5;

// Escape Character
String sentinel = "#";

Morse obj = Morse(led_pin);

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets led_pin to an output
  pinMode(led_pin, OUTPUT);
}

void loop() {

  String test_variable;

  while (test_variable.equals(sentinel))
  {
    test_variable = Serial.readString();
    obj.sendUserMessage(test_variable);
  // Serial.println(obj.pin);
  // digitalWrite(5, HIGH);
  }
}
