#ifndef __STATEPRESON_H__
#define __STATEPRESON_H__

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif

#include <SoftwareSerial.h>

class StatePerson
{
    enum
    {
        stage1 = 1,
        stage2 = 2,
        stage3 = 3,
        

    };

public:
    int dangerLevel = 10;
    void begin(SoftwareSerial &mySerial);
    String checkBloodPressure(float systolic, float diastolic);
    String checkBloodOxygen(int age, float spo2);
    String checkHeartRate(int age, float heartRate);
    String checkBloodPressure(int age, String gender);
    String ageLevel(int age);
    void sendSms(String message, String number, SoftwareSerial &mySerial);
    void alertDoctor(String number, SoftwareSerial &mySerial);
    void updateSerial(SoftwareSerial &mySerial);
    void alert();
    void testBody(String Blood ,String heartRate,String temp,String spo2);
};

#endif // __STATEPERSON_H__