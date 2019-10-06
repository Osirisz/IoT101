const int SWITCHPIN = 12;     // the number of the pushbutton pin
const int LEDPIN = 14;
int buttonState = 0;
bool isLight = false;

void setup() {
  pinMode(SWITCHPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  buttonState = digitalRead(SWITCHPIN);
  Serial.println(buttonState);
  delay(100);

  if (isLight) {
    if (buttonState == 1) {
      digitalWrite(LEDPIN, LOW);
      isLight = false;
    }
  } else {
    if (buttonState == 1) {
      digitalWrite(LEDPIN, HIGH);
      isLight = true;
    }
  }
}
