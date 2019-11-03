#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"


//Define WiFi parameters
const char* ssid = "Username";
const char* password = "Password";


//Create WiFi Client and PubSub Client Object
WiFiClient wifiClient;

//Declare DHT sensor section
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


char mqttUserName[] = "My_Name";  // Use any name.
char mqttPass[] = "MQTTAPIKEY";      // Change to your MQTT API Key from Account > MyProfile.   
char writeAPIKey[] = "writeAPIKey";    // Change to your channel write API key.
long channelID = channel_number;                    // Change to your channel ID.

static const char alphanum[] ="0123456789"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz";  // For random generation of client ID.
   

PubSubClient mqttClient(wifiClient); // Initialize the PubSubClient library.
const char* server = "mqtt.thingspeak.com";  
                          
unsigned long lastConnectionTime = 0; 
const unsigned long postingInterval = 20000; // Post data every 20 seconds.

void setup() 
{
  Serial.begin(115200);
  setup_wifi();
  dht.begin();
  mqttClient.setServer(server, 1883);   // Set the MQTT broker details.
}

void loop() 
{ 
  if (!mqttClient.connected()) 
  {
    reconnect();
  }

  mqttClient.loop();   // Call the loop continuously to establish connection to the server.

  // If interval time has passed since the last connection, publish data to ThingSpeak.
  if (millis() - lastConnectionTime > postingInterval) 
  {
    mqttPublishFeed(); // Publish three values simultaneously.
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

void reconnect() 
{
  char clientID[9];

  // Loop until reconnected.
  while (!mqttClient.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Generate ClientID
    for (int i = 0; i < 8; i++) {
        clientID[i] = alphanum[random(51)];
    }
    clientID[8]='\0';

    // Connect to the MQTT broker.
    if (mqttClient.connect(clientID,mqttUserName,mqttPass)) 
    {
      Serial.println("connected");
    } else 
    {
      Serial.print("failed, rc=");
      // Print reason the connection failed.
      // See https://pubsubclient.knolleary.net/api.html#state for the failure code explanation.
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttPublishFeed() {
  
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
  
  // Create data string to send to ThingSpeak.
  String data = String("field1=") + String(t, DEC) + "&field2=" + String(h, DEC);
  int length = data.length();
  const char *msgBuffer;
  msgBuffer=data.c_str();
  Serial.println(msgBuffer);
  
  // Create a topic string and publish data to ThingSpeak channel feed. 
  String topicString = "channels/" + String( channelID ) + "/publish/"+String(writeAPIKey);
  length = topicString.length();
  const char *topicBuffer;
  topicBuffer = topicString.c_str();
  mqttClient.publish( topicBuffer, msgBuffer );
  lastConnectionTime = millis();
}
