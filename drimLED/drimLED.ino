const int LEDPIN = 14;

void setup() {
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  for (int fadeValue = 0; fadeValue <= 255; fadeValue++) {
    analogWrite(LEDPIN, fadeValue);
    delay(50);
  }

  for (int fadeValue = 255; fadeValue >= 0; fadeValue--) {
    analogWrite(LEDPIN, fadeValue);
    delay(50);
  }
}
