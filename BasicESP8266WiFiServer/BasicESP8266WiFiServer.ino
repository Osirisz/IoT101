#include <ESP8266WiFi.h>

const char* ssid = "Your SSID Name";
const char* password = "Your Password";

WiFiServer server(80); // port

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print(F("Connecting to "));
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(". ");
  }

  Serial.println();
  Serial.print(F("Connected, Your IP is "));
  Serial.println(WiFi.localIP());

  server.begin();
}

// prepare a web page to be send to a client (web browser)
String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "Analog input:  " + String(analogRead(A0)) +
            "</html>" +
            "\r\n";
  return htmlPage;
}

void loop() {
  WiFiClient client = server.available();
  if (client){
    Serial.println("\n[Client connected]");
    while (client.connected()){
      // read line by line what the client (web browser) is requesting
      if (client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n'){
          client.println(prepareHtmlPage());
          break;
        }
      }
    }
  }
}
