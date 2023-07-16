#include <Arduino.h>
#include "HeartRate.h"

HeartRate heart;
// Callback routine is executed when a pulse is detected
void onBeatDetected() {
    Serial.println("Beat!");
}
void setup() {

Serial.begin(115200);
heart.setup();
heart.pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  
  heart.readHeartRate();
  heart.readOxygenSaturation();
}

