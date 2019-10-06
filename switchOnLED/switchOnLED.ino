const int SWITCHPIN = 12;
const int LEDPIN = 14;
int buttonState = 0;


void setup() {
  pinMode(SWITCHPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  buttonState = digitalRead(SWITCHPIN);
  Serial.println(buttonState);
  delay(100);

  if (buttonState == 1) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
}
