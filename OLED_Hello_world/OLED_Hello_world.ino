#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // point is Reset OLED
Adafruit_SSD1306 display(-1); // point is not set Reset pin OLED

void setup() {
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
  display.drawPixel(0,0, WHITE);
  display.drawPixel(127,0, WHITE);
  display.drawPixel(0,63, WHITE);
  display.drawPixel(127,63, WHITE);

  display.drawCircle(5,5,5,WHITE);
  display.fillCircle(5,5,3,WHITE);

  display.drawCircle(120,5,5,WHITE);
  display.fillCircle(120,5,3,WHITE);

  display.drawFastHLine(45, 50, 40, WHITE);

  display.fillTriangle(62, 15, 60, 20, 64, 20, WHITE);
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,30);
  display.println("Earth");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

}
