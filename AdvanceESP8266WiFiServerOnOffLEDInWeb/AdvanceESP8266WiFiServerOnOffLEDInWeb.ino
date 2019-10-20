#include <ESP8266WiFi.h>

// Replace with your network details
const char* ssid = "Your SSID Name";
const char* password = "Your Password";

// Web Server on port 80
WiFiServer server(80);

// variables
String header;
String output2_State = "off";
String output16_State = "off";
const int gpio2_pin = 2;
const int gpio16_pin = 16;

void setup() {
  Serial.begin(115200);
  
  // preparing GPIOs
  pinMode(gpio2_pin, OUTPUT);
  pinMode(gpio16_pin, OUTPUT);
  digitalWrite(gpio2_pin, HIGH);
  digitalWrite(gpio16_pin, HIGH);
  
  // Connecting to WiFi network
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". ");
  }
  Serial.println(F(""));
  Serial.println(F("Connection Successful!"));
  
  
  // Starting the web server
  server.begin();
  Serial.print(F("Web server running. Point your browser to "));
  Serial.println(WiFi.localIP());
}

void loop() {
WiFiClient client = server.available();   // Listen for incoming clients

if (client) {                             // If a new client connects,
    Serial.println("\n[Client connected]");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              output2_State = "on";
              digitalWrite(gpio2_pin, LOW);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              output2_State = "off";
              digitalWrite(gpio2_pin, HIGH);
            } else if (header.indexOf("GET /16/on") >= 0) {
              Serial.println("GPIO 16 on");
              output16_State = "on";
              digitalWrite(gpio16_pin, LOW);
            } else if (header.indexOf("GET /16/off") >= 0) {
              Serial.println("GPIO 16 off");
              output16_State = "off";
              digitalWrite(gpio16_pin, HIGH);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 2 
            client.println("<p>GPIO 2 - State " + output2_State + "</p>");
            // If the output2State is off, it displays the ON button       
            if (output2_State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 16
            client.println("<p>GPIO 16 - State " + output16_State + "</p>");
            // If the output16State is off, it displays the ON button       
            if (output16_State=="off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
