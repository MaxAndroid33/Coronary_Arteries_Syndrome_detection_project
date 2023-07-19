#include "ScreenDisplay.h"
#include <TFT_22_ILI9225.h>
#include "SPIFFS.h"
#include "HeartRate.h"
#include "Connection.h"
const char *ssid = "root";
const char *password = "maxmax123";

Connection connection(ssid, password);
SPIClass hspi(HSPI);

ScreenDisplay lcd;
HeartRate heart;

// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
    lcd.setText(0,90,"Beat !!");
    
}
void setup()
{

    Serial.begin(115200);
    lcd.setup(hspi);
    lcd.setText(0, 0, "Connection To WiFi...");
    connection.setup(false);
    lcd.clearScreen();
    lcd.setText(50, 50, "Connected ");
    delay(3000);
    lcd.clearScreen();
    lcd.setText(0,0, "Enter The Profile Info");
    lcd.setText(0,35, "In WebPage :");
    lcd.setText(0, 70, "http://" + connection.ip.toString());
    connection.checkOneTimeSetup();
    lcd.clearScreen();
    lcd.setText(50, 0, "Successfully");
    lcd.setText(0, 35, "Completed The Profile");
    delay(3000);
    lcd.clearScreen();
    Serial.print(connection.readAllData());
    // heart.setup();
    // heart.pox.setOnBeatDetectedCallback(onBeatDetected);

    
        // heart.setup();
}

void loop()
{

}