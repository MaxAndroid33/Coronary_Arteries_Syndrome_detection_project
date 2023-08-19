#include "TempSensor.h"

TempSensor::TempSensor(uint8_t tempPin) : tempPin(tempPin)
{
}

void TempSensor::begin()
{
    oneWire.begin(tempPin);
    tempSensor.setOneWire(&oneWire);

    tempSensor.begin();
}
float TempSensor::readTemperature()
{

    tempSensor.requestTemperatures();
    float tempC = tempSensor.getTempCByIndex(0);
    if (int(tempC) == -127)
    {   
        return temperature;
    }
    else
    {
        temperature = tempC;
        return temperature;
    }
}
