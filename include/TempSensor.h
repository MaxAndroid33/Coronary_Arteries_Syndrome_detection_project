#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif

#ifndef __SCREENDISPLAY_H
#define __SCREENDISPLAY_H
#include "ScreenDisplay.h"
#endif

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TempSensor
{
    OneWire oneWire;
    DallasTemperature tempSensor;
    volatile uint8_t tempPin;

public:
    float temperature =0;
     TempSensor(uint8_t tempPin);
    void begin();
    float readTemperature();
    String checkTemperatureBody();


};

#endif // __TEMPSENSOR_H__