#include "ESP8266WiFi.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(-1); // point is not set Reset pin OLED

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {    
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      if(WiFi.SSID(i) == "ssid_name") { // change
        Serial.print(WiFi.SSID(i));
        Serial.print(": ");
        Serial.print(WiFi.RSSI(i));
        Serial.print(" dbm");
        
        display.print(WiFi.SSID(i));
        display.print(": ");
        display.print(WiFi.RSSI(i));
        display.print(" dbm");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,30);
        display.display();
        i = n;
      }
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(1000);
}
