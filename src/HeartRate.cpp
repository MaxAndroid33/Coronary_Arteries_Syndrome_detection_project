
#include "HeartRate.h"

void HeartRate::setup()
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
    // Initialize sensor
    if (!pox.begin())
    {
        Serial.println("FAILED");
        for (;;)
            ;
    }
    else
    {
        Serial.println("SUCCESS");
    }
    // Configure sensor to use 7.6mA for LED drive
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}

float HeartRate::readHeartRate()
{
    // Update the pulse oximeter
    pox.update();
    // Get heart rate
    float heartRate = pox.getHeartRate();
    Serial.print("Heart Rate: ");
    Serial.print(heartRate);

    // Delay for a short period before the next reading
    delay(100);

    return heartRate;
}

float HeartRate::readOxygenSaturation()
{
    // Update the pulse oximeter
    pox.update();
    // Get oxygen saturation reading
    float oxygenSaturation = pox.getSpO2();

    Serial.print(" bpm, SpO2: ");
    Serial.print(oxygenSaturation);
    Serial.println("%");

    // Delay for a short period before the next reading
    delay(100);

    return oxygenSaturation;
}
