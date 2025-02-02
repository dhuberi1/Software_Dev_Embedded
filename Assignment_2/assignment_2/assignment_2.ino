

void setup() {
  // Opens Serial on 9600 baud rate
  Serial.begin(9600);

  // Sets pin A0 to an input
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = analogRead(A0);
  double mv = a * (5000/1024.0);
  double c = (mv - 500)/10;
  double f = (c * 9/5.0) + 32;
  Serial.println(a);
  Serial.println(mv);
  Serial.println(c);
  Serial.println(f);
}
