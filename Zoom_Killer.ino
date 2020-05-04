/* Zoom_Killer.ino
 * 
 * Monitor and kill Zoom
 */

#include "interfaces.h"
#include "wifi_client.h"
#include "variables.h"
#include "http_client.h"


boolean networkState = false;


// Set up interfaces, connect to the WiFi network, and illuminate default LEDs.
void setup() {
  delay(1000);
  Serial.begin(115200);

  pinMode(zoomOnLed, OUTPUT);
  pinMode(zoomOffLed, OUTPUT);
  pinMode(spawnButton, INPUT);
  pinMode(killButton, INPUT);

  networkState = connWifi(ssid, password);
  if ( !networkState) {
    sleep();
  }
  
  updateLeds(zoomOffLed, true);
}


// Evaluate the status of each interface, check the status of Zoom on the server, 
// perform requested actions, and update hardware LEDs to represent the status.
void loop() {
  boolean killButtonState = monButton(killButton);
  boolean spawnButtonState = monButton(spawnButton);

  String destination = "http://" + srvName + ":" + String(srvPort);
  postRequests(killButtonState, spawnButtonState);
  httpPost(killButtonState, spawnButtonState, destination);

  boolean zoomRunState = zoomState(destination);
  if (! zoomRunState){
    updateLeds(zoomOnLed, false);
    updateLeds(zoomOffLed, true);
  }
  
  Serial.println();
  delay(500);
}


// If the hardware fails to connect to a wireless network, then enter deep sleep.
void sleep() {
  Serial.println("Going to sleep!");
  ESP.deepSleep(30e6);
}
