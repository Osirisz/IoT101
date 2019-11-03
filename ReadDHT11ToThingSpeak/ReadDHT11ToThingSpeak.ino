#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include "DHT.h"

//Define WiFi parameters
//const char* ssid = "Username";
//const char* password = "Password";


const char* ssid = "Jaturat";
const char* password = "0616653987";

//Create WiFi Client and PubSub Client Object
WiFiClient wifiClient;

//Declare DHT sensor section
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Declare ThingSpeak section
unsigned long myChannelNumber = 901139; //change
const char* myWriteAPIKey = "M1Q2JG4FICO9D1K5"; //change
String myStatus = "";

//Define loop variables
unsigned long previousMillis = 0;
const long interval = 20000;

void setup() 
{
  Serial.begin(115200);
  setup_wifi();
  ThingSpeak.begin(wifiClient);
  dht.begin();
}

void loop() 
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) 
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.println("*C");
    
    // set the fields with the values
    ThingSpeak.setField(1, (int) t);
    ThingSpeak.setField(2, (int) h);
    
    // figure out the status message
    if((int)t >= 28)
    {
      myStatus = String("Air condition is closed"); 
    }
    else
    {
      myStatus = String("Air condition is opened");
    }

    // set the status
    ThingSpeak.setStatus(myStatus);
    
    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200)
    {
      Serial.println("Channel update successful.");
    }
    else
    {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    } 
  }
}

void setup_wifi()
{
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s ", ssid);

  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print(F("Connected, Your IP is "));
  Serial.println(WiFi.localIP());
}
