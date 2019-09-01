const int LED1 = 16;
const int LED2 = 2;
long counter = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  if(counter %2 == 0){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(1000);
  } else {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(1000);
  }
  counter += 1;
}
