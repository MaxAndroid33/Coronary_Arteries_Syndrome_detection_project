#ifndef __HEARTRATE_H__
#define __HEARTRATE_H__

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif
#ifndef __WIRE_H
#define __WIRE_H
#include <Wire.h>
#endif

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