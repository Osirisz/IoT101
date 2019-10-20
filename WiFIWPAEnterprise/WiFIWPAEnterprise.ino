#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
#include "wpa2_enterprise.h"
}

static const char* ssid = "KMUTT-Secure";
static const char* username = "myusername";
static const char* password = "mypassword";

void setup() {
  Serial.begin(115200);
  Serial.println("Free memory before connection sucessful");
  Serial.println(system_get_free_heap_size());
  
  //wifi_set_opmode(STATION_MODE);
  WiFi.mode(WIFI_STA);
  
  struct station_config wifi_config;
  
  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
  
  wifi_station_set_config(&wifi_config);
  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_identity((uint8*)username, strlen(username));
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));
  wifi_station_connect();
  
  // Wait for connection AND IP address from DHCP
  Serial.println();
  Serial.println("Waiting for connection and IP Address from DHCP");
  
  while (WiFi.status() != WL_CONNECTED) {
   Serial.println("Free memory during connecting to wifi");
    Serial.println(system_get_free_heap_size());
    delay(2000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected! Your IP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Free memory after connection sucessful");
  Serial.println(system_get_free_heap_size());
}

void loop() {
// put your main code here, to run repeatedly:

}
