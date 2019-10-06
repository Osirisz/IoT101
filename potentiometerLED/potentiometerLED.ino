const int POTENPIN = A0;
const int LEDPIN = 14;
int potenVal = 0;
int ledVal = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  potenVal = analogRead(POTENPIN);
  Serial.println(potenVal);
  ledVal = map(potenVal, 0, 1024, 0, 255);
  analogWrite(LEDPIN, ledVal);
  delay(50);
}
