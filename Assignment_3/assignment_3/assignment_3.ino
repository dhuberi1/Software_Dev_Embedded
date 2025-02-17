// IR detector pin
int IR_pin = 2;

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
}

void loop() {
  Serial.println(count);
}
