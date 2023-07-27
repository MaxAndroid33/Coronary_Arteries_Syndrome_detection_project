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
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class TempSensor
{
    Adafruit_BME280 bme; // I2C
public:
    void setup(ScreenDisplay &lcd);
    float readTemperature();

};


#endif // __TEMPSENSOR_H__