#ifndef __Pages_H__
#define __Pages_H__

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif

#ifndef __SCREENDISPLAY_H
#define __SCREENDISPLAY_H
#include "ScreenDisplay.h"
#endif


#include "HeartRate.h"
#include "DetectMoving.h"
#include "TempSensor.h"
class Pages
{
int pageNum = 0;
int16_t w;
ScreenDisplay  lcd;

public:
     
 int16_t heartRatePage(ScreenDisplay & lcd);
int16_t statePage(ScreenDisplay & lcd);
    void selectPage(ScreenDisplay & lcd);
    void slidePage(ScreenDisplay & lcd);
    void heartRatePageValues(ScreenDisplay & lcd,HeartRate &heart,DetectMoving &moving , TempSensor &temp);
    void statePageValues(ScreenDisplay & lcd,String HR ,String SPO2 ,String BP  ,float lastHeartRate ,float lastSpo2);
    
};
#endif // __Pages_H__