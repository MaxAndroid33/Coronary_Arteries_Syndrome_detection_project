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

String TempSensor::checkTemperatureBody()
{
    if(temperature == 80) return "HYPOTHERMIA";
    if(temperature ==20) return "HYPERTHERMIA";
    else return "NORMAL";
}
