
#include "TempSensor.h"

void TempSensor::setup(ScreenDisplay &lcd)
{
    int count = 0;
    while (!bme.begin())
    {
        if (count == 0)
        {
            lcd.setText(0, 0, "Failed Initialize ");
            lcd.setText(0, 35, "Temperature Sensor ");
        }
        count++;
        if(count =10) break;
    }
    lcd.clearScreen();
    lcd.setText(0, 0, "Successfully");
    lcd.setText(0, 35, "Detect");
    lcd.setText(0, 70, "Temperature Sensor ");
}

float TempSensor::readTemperature()
{

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    return bme.readTemperature();
}
