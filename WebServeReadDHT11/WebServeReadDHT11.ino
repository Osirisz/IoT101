#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11
String humidity = "";
String temperature = ""; 
String heatIndex = "";

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
ESP8266WebServer server(80);

const char* ssid = "Your SSID";
const char* password = "Your Password";

const int led = 2;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  WiFi.mode(WIFI_STA); //เปลี่ยนการทำงานเป็น Station mode
  WiFi.begin(ssid, password); //เริ่มเชื่อมต่อ WiFi
  dht.begin();

  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(". ");
  }

  Serial.println();
  Serial.print("Connected!, Your IP is ");
  Serial.println(WiFi.localIP());

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started!");
}

void loop() {
  server.handleClient();
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(1000);

  humidity = "Humidity: " + String(h) + "%";
  temperature = "Temperature: " + String(t) + " oC, " + String(f) + " oF"; 
  heatIndex = "Heat index: " + String(hic) + " oC " + String(hif) + " oF";
  server.on("/", handleRoot);
}

void handleRoot() {
  server.send(200, "text/html", "<head><meta http-equiv='refresh' content='2'/></head><form><h1>"+humidity+"<br>"+temperature+"<br>"+heatIndex+"</h1></form>");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: File Not Found");
}
