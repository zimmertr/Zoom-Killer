/* interefaces.h
 * 
 * Declare all hardware interfaces and manage their states.
 */

// Interfaces
const uint8_t spawnButton = D1;
const uint8_t killButton = D2;
const uint8_t zoomOnLed = D4;
const uint8_t zoomOffLed = D3;


boolean monButton(uint8_t button) {
  boolean buttonState = digitalRead(button);

  if (buttonState == HIGH) {
    return true;
  }
  else {
    return false;
  }
}


void postRequests(boolean spawnButtonState, boolean killButtonState){
  Serial.println("Requests:");

  if (killButtonState){
    Serial.println("- Kill Requested!");
  }

  if (spawnButtonState){
    Serial.println("- Spawn Requested!");
  }
}


void updateLeds(uint8_t light, boolean state) {
    if (state){
      digitalWrite(light, HIGH);
    }else{
      digitalWrite(light, LOW);
    }
}
