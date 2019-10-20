#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

WiFiClient client; // Create an instance of the WiFiClient class, called 'client'
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

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

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {
  server.send(200, "text/plain", "Hello world!");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
