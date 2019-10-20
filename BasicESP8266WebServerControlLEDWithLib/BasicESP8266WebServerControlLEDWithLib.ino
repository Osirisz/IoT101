#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client;
ESP8266WebServer server(80);

const char* ssid = "Your SSID";
const char* password = "Your Passoword";

const int led = 2;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  WiFi.mode(WIFI_STA); //เปลี่ยนการทำงานเป็น Station mode
  WiFi.begin(ssid, password); //เริ่มเชื่อมต่อ WiFi

  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(". ");
  }

  Serial.println();
  Serial.print("Connected!, Your IP is ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/LED", HTTP_POST, handleLED);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started!");
}

void loop() {
  server.handleClient();
}

void handleRoot(){
  server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");  
}

void handleLED(){
  digitalWrite(led,!digitalRead(led));
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: File Not Found");
}
