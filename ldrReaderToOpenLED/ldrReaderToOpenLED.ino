const int LDRPIN = A0;
const int LEDPIN = 14;
int ldrVal = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  ldrVal = analogRead(LDRPIN);
  Serial.println(ldrVal);
  if(ldrVal > 200) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
  delay(50);
}
