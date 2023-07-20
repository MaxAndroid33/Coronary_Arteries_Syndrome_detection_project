
#include "HeartRate.h"

void HeartRate::setup(ScreenDisplay &lcd)
{
    int count = 0;
    
    // Initialize sensor
    while (!pox.begin())
    {
        if (count == 0)
        {
            lcd.setText(20, 0, "Failed Initialize ");
            lcd.setText(0, 35, "HeartRate Sensor ");
        }
        count++;
    }

    lcd.clearScreen();
    lcd.setText(20, 0, "Successfully");
    lcd.setText(40, 35, "Detect");
    lcd.setText(0, 70, "HeartRate Sensor ");
    delay(3000);

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
    Serial.println(heartRate);

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
