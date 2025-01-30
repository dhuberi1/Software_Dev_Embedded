#include "Morse.h"

// Digital Output Pin for LED
int led_pin = 5;

// Escape Character
String sentinel = "#";

// Boolean that checks if the loop has been escaped
bool escaped = false;

Morse obj = Morse(led_pin);

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets led_pin to an output
  pinMode(led_pin, OUTPUT);
}

void loop() {

  while (escaped == false)
  {
    String test_variable;

    // Reads serial input as string
    test_variable = Serial.readString();
    test_variable.trim();

    // Checks that a string was entered into the serial
    if (test_variable.equals("") == false)
    {
      Serial.println(test_variable);
      
      // Checks if escape character is entered
      if (test_variable.equals(sentinel) == true)
      {
        Serial.println("Loop Terminated!");
        escaped = true;
      }
      else
      {
        obj.sendUserMessage(test_variable);
      }
    }
  }
}
