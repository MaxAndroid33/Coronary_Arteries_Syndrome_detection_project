#ifndef __DETECTMOVING_H
#define __DETECTMOVING_H


#include <Arduino.h>
#include <Wire.h>
#include <LSM303.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#define SDA_PIN 21
#define SCL_PIN 22

class DetectMoving {

LSM303 compass;
float oldX, oldY, oldZ;
float newX, newY, newZ;
float differenceThreshold = 500;  // Adjust this value as per the sensitivity you want
public:

void setup();

bool detectMoving(); //return ('true' means moving , 'false' means not moving )


};

#endif // __DETECTMOVING_H