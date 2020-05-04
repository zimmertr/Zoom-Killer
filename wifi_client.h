/* interefaces.h
 * 
 * Connect to a WiFi network.
 */

#include "ESP8266WiFi.h"


boolean connWifi(const char* ssid, const char* password) {
  Serial.println("\n******************************");
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);
  uint8_t attempts = 1;

  while (attempts < 31) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
      attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("Connection Successful!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      Serial.print("Subnet Mask: ");
      Serial.println(WiFi.subnetMask());
      Serial.print("Gateway Address: ");
      Serial.println(WiFi.gatewayIP());
      Serial.println("******************************\n");
      return true;
    }
  }
  
  Serial.println("\nConnection Failed!");
  return false;
}
