#include "ScreenDisplay.h"
#include <TFT_22_ILI9225.h>
#include "SPIFFS.h"
#include "HeartRate.h"


SPIClass hspi(HSPI);

ScreenDisplay lcd;
HeartRate heart;



// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
}
void setup()
{

    Serial.begin(115200);
    connection.setup(false);
    Serial.print(connection.readAllData());
    connection.checkOneTimeSetup();
    Serial.print(connection.readAllData());
    // heart.setup();
    // heart.pox.setOnBeatDetectedCallback(onBeatDetected);
    lcd.setup(hspi);
    lcd.displaySetup("HelloWord!!");
    heart.setup();
    

}

void loop()
{
    //lcd.clearScreen();

    lcd.setText(20,15,"yosif");
    // delay(2000);
    
    lcd.displayHeartRate(heart.readHeartRate());
    lcd.displaySpO2(heart.readOxygenSaturation());

    // delay(2000);
    // lcd.clearScreen();
    // lcd.displaySpO2(200);

    

}