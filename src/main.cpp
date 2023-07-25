#include "ScreenDisplay.h"
#include <TFT_22_ILI9225.h>
#include "HeartRate.h"
#include "Connection.h"
#include "DetectMoving.h"
#include "StatePerson.h"

const char *ssid = "root";
const char *password = "maxmax123";

Connection connection(ssid, password);
SPIClass hspi(HSPI);

ScreenDisplay lcd;
HeartRate heart;
DetectMoving moving;
StatePerson state;

// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
    lcd.setText(0, 90, "Beat !!");
}
void setup()
{
    // Initialize All Sensors 
    Serial.begin(115200);
    lcd.setup(hspi);
    lcd.tft.setOrientation(3);
    moving.setup(lcd);
    lcd.clearScreen();
    heart.setup(lcd);
    heart.pox.setOnBeatDetectedCallback(onBeatDetected);
    lcd.clearScreen();


    
    connection.setup(lcd);
    lcd.clearScreen();
    lcd.setText(0, 0, "Enter The Profile");
    lcd.setText(0, 35, "Info In WebPage:");
    lcd.setText(0, 70, "http://" );
     lcd.setText(0, 105, connection.ip.toString() );
    
    lcd.setText(0, 140, "WiFiName:"+String(ssid));
    lcd.setText(0, 175, "Pass:"+String(password));
    
    connection.checkOneTimeSetup();
    lcd.clearScreen();
    lcd.setText(20, 0, "Successfully");
    lcd.setText(20, 35, "Completed");
    lcd.setText(0, 75, "Patient Profile");
    delay(3000);
    lcd.clearScreen();
    Serial.print(connection.readAllData());

}

void loop()
{
        
}