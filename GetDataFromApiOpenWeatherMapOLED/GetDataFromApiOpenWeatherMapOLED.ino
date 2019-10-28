#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     LED_BUILTIN // Reset pin # (or -1 if sharing Arduino reset pin)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // point is Reset OLED
Adafruit_SSD1306 display(-1); // point is not set Reset pin OLED

const char* ssid = "Your SSID";
const char* password = "Your Password";

WiFiClient client;

const long interval = 30000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s", ssid);
  Serial.println("");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected, You IP is ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();
  String apiKey = "7fd995fcede4c13981cce642b5c11424";
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;
      http.begin("http://api.openweathermap.org/data/2.5/weather?q=Bangkok&units=metric&appid=" + apiKey);
      int httpCode = http.GET();
      if (httpCode > 0)
      {
        const size_t capacity = JSON_ARRAY_SIZE(3) + 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12);
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, http.getString()); // แตกค่าค่า JSON มาเป็น value
        
        JsonArray weather = doc["weather"];
        JsonObject weather_0 = weather[0];
        const char* weather_0_main = weather_0["main"];
        
        JsonObject main = doc["main"];
        float main_temp = main["temp"];
        int main_humidity = main["humidity"];

        float wind_speed = doc["wind"]["speed"];

        Serial.print("Weather Condition: ");
        Serial.println(weather_0_main);
        Serial.print("Temperature: ");
        Serial.println(main_temp,2);
        Serial.print("Humidity: ");
        Serial.println(main_humidity);
        Serial.print("Wind speed: ");
        Serial.println(wind_speed); 
        Serial.println();

        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,10);
        display.print("Weather Condition: ");
        display.println(weather_0_main);
        display.print("Temperature: ");
        display.println(main_temp,2);
        display.print("Humidity: ");
        display.println(main_humidity);
        display.print("Wind speed: ");
        display.println(wind_speed);
        display.display();
      }
      http.end();
      
    }
  }
}
