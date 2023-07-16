#ifndef __HEARTRATE_H__
#define __HEARTRATE_H__

#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

class HeartRate{


public:
// Create a PulseOximeter object
PulseOximeter pox;

void setup();
float readHeartRate();
float readOxygenSaturation();

};


#endif // __HEARTRATE_H__