#ifndef __DETECTMOVING_H
#define __DETECTMOVING_H

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif
#ifndef __WIRE_H
#define __WIRE_H
#include <Wire.h>
#endif

#ifndef __SCREENDISPLAY_H
#define __SCREENDISPLAY_H
#include "ScreenDisplay.h"
#endif

#include <LSM303.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>

#define SDA_PIN 21
#define SCL_PIN 22

class DetectMoving {

LSM303 compass;
float oldX, oldY, oldZ;
float newX, newY, newZ;
float differenceThreshold = 500;  // Adjust this value as per the sensitivity you want
public:

void setup(ScreenDisplay &lcd);

bool detectMoving(); //return ('true' means moving , 'false' means not moving )


};

#endif // __DETECTMOVING_H