/* http_client.h
 * 
 * Perform HTTP requests to a server.
 */

#include "ESP8266HTTPClient.h"


// Check whether or not Zoom is running on a server.
boolean zoomState(String destination){
  HTTPClient http;
  http.begin(destination);
  String rspContent = http.getString();
  http.end();
  
  if (rspContent == "Yes"){
    return true;
  }
  else{
    return false;
  }
}


// Send a HTTP request to the server instructing it to kill Zoom
void killZoom(String destination){
  updateLeds(zoomOnLed, false);
  updateLeds(zoomOffLed, true);
  
  HTTPClient http;
  destination = destination + "/killzoom";
  http.begin(destination);
  int rspCode = http.GET();
  String rspContent = http.getString();
  http.end();
}


// Send an HTTP request to the server instructing it to spawn Zoom.
void spawnZoom(String destination){
  updateLeds(zoomOnLed, true);
  updateLeds(zoomOffLed, false);
  
  HTTPClient http;
  destination = destination + "/spawnzoom";
  http.begin(destination);
  int rspCode = http.GET();
  String rspContent = http.getString();
  http.end();
}


// Drive the requested actions.
void httpPost(boolean spawnButtonState, boolean killButtonState, String destination){
  Serial.println("Actions:");

  if (killButtonState){
    killZoom(destination);
    Serial.println("- Zoom Killed!");
  }
  if (spawnButtonState){
    spawnZoom(destination);
    Serial.println("- Zoom Spawned!");
  }
}
