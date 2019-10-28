#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA); //เปลี่ยนการทำงานเป็น Station mode
  WiFi.begin(ssid, password); //เริ่มเชื่อมต่อ WiFi

  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected!, Your IP is ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http; //สร้าง object http
    http.begin("http://www.example.com"); //เรียก method begin 
    int httpcode = http.GET(); //เอา httpcode จาก method GET ไปเก็บในตัวแปร httpcode

    if (httpcode > 0) {
      String payload = http.getString(); //เอา payload ที่ได้เก็บเข้าตัวแปร payload
      Serial.println(payload); //print payload ออกทาง serial monitor
    }
    http.end();
  }
  delay(10000);
}
