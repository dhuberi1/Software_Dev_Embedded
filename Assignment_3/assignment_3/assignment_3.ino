int IR_pin = A0;

//int IR_thresh = ;

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets pin temp_pin to an input
  pinMode(IR_pin, INPUT);

}

void loop() {
  int IR_detect = analogRead(IR_pin);
  Serial.println(IR_detect);
}
