#include <ESP8266WiFi.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";

const char* host = "www.example.com";

String get1 = "GET / HTTP/1.1\r\n";
String get2 = "HOST: ";
String get3 = "User-Agent: ESP8266\r\n";
String get4 = "Accept: */*\r\n";
String get5 = "Connection: close\r\n";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //เปลี่ยนการทำงานเป็น Station mode
  WiFi.begin(ssid, password); //เริ่มเชื่อมต่อ WiFi

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected!, Your IP is ");
  Serial.println(WiFi.localIP());

}

void loop() {
  WiFiClient client;
  Serial.printf("\n[Connecting to %s ...", host);

  if (client.connect(host, 80)){ //ถ้าเชื่อมต่อผ่าน port 80 ได้
    Serial.println("Connected!]");
    Serial.println("[Sending a http request]");

    client.print(get1 + get2 + host + "\r\n" + get3 + get4 + get5 + "\r\n");
    Serial.print(get1 + get2 + host + "\r\n" + get3 + get4 + get5 + "\r\n");

    Serial.println("[Response:]");
      while(client.connected()){
        if(client.available()){
          String line = client.readStringUntil('\n');
          Serial.println(line);
        }
      }
    client.stop();
    Serial.println("[Disconnected]");
}else{
  Serial.println("Connection failed!]");
  client.stop();
}
  delay(10000);
}
