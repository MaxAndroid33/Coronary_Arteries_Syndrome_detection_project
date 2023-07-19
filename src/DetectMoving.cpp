
#include "DetectMoving.h"

void DetectMoving::setup()
{
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN); // Set the SDA and SCL pins
        while (!compass.init())
            Serial.println("Failed to detect and initialize compass!");  
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
