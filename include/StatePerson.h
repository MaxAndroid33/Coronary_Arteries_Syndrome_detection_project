#ifndef __STATEPRESON_H__
#define __STATEPRESON_H__

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif



class StatePerson
{

   
public:
    String checkBloodPressure(float systolic ,float diastolic);
    String checkBloodOxygen(int age ,float spo2);
    String checkHeartRate(int age ,float heartRate);
    String checkBloodPressure(int age ,String gender) ;
    String ageLevel(int age);

    
};






#endif // __STATEPRESON_H__