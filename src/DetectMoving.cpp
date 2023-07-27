
#include "DetectMoving.h"

void DetectMoving::setup(ScreenDisplay &lcd)
{   int count =0;
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN); // Set the SDA and SCL pins
        while (!compass.init()){
            if(count==0){
            lcd.setText(0,0,"Failed Initialize ");
            lcd.setText(0,35,"Moving Sensor "); 
            }
            count++;
        }
        lcd.clearScreen();
        lcd.setText(0,0,"Successfully");
        lcd.setText(0,35,"Detect");
        lcd.setText(0,70,"Moving Sensor ");
    compass.enableDefault();
}

bool DetectMoving::detectMoving()
{
    bool state;
    compass.read();

    /* Get the new X, Y and Z values */
    newX = compass.a.x;
    newY = compass.a.y;
    newZ = compass.a.z;

    /* Compare the old and new values to see if they have changed beyond the threshold */
    if (abs(newX - oldX) > differenceThreshold || abs(newY - oldY) > differenceThreshold || abs(newZ - oldZ) > differenceThreshold)
    {
        Serial.println("patient is moving");
        state = true;
    }
    else
    {
        Serial.println("patient not is moving");
        state = false;
    }

    /* Save the current values as the old values for the next loop */
    oldX = newX;
    oldY = newY;
    oldZ = newZ;

    return state;
}
