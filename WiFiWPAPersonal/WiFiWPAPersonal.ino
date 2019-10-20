#include <ESP8266WiFi.h>

const char* ssid = "myssid";
const char* password = "mypassword";

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print(F("Connecting to "));
  Serial.print(ssid);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(F("."));
    Serial.print(" ");
  }

  Serial.println();
  Serial.print(F("Connected, Your IP is "));
  Serial.println(WiFi.localIP());
}

void loop() {
}
