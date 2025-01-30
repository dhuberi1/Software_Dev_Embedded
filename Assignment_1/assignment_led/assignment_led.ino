#include "Morse.h"

Morse obj = Morse(5);

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  String test_variable = Serial.readString(); 
  // obj.dash();
  obj.sendUserMessage(test_variable);
  // Serial.println(obj.pin);
  // digitalWrite(5, HIGH);
}
