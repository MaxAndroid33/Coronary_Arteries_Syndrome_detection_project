#include "ScreenDisplay.h"
#include <TFT_22_ILI9225.h>
#include "HeartRate.h"
#include "Connection.h"
#include "DetectMoving.h"
#include "StatePerson.h"
#include "Pages.h"
#include "TempSensor.h"

#define SELECT_PAGE_PIN_BTN 27
const char *ssid = "root";
const char *password = "maxmax123";

Connection connection(ssid, password);
SPIClass hspi(HSPI);

ScreenDisplay lcd;
HeartRate heart;
DetectMoving moving;
StatePerson state;
Pages setPage;
TempSensor temp;
int16_t w;
int onceSlide = 0;
float lastHarRate = 0.0, lastSpo2 = 0.0;
// Callback routine is executed when a pulse is detected
// void onBeatDetected()
// {
//     lcd.setText(20, 120, "Beat !!", true, 0, 20, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_RED);
// }

void slidePage()
{
    lcd.clearScreen();
    setPage.slidePage(lcd);
}
void setup()
{
    // Initialize All Sensors
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(SELECT_PAGE_PIN_BTN), slidePage, RISING);
    lcd.setup(hspi);
    lcd.tft.setOrientation(3);
    lcd.clearScreen();
    // Temperature Setup Sensor
    temp.setup(lcd);
    delay(1000);
    lcd.clearScreen();
    // Moving Setup Sensor
    moving.setup(lcd);
    delay(1000);
    lcd.clearScreen();
    // HeartRate Setup Sensor
    heart.setup(lcd);
    // heart.pox.setOnBeatDetectedCallback(onBeatDetected);
    delay(1000);
    lcd.clearScreen();

    // WiFi Setup Connection
    connection.setup(lcd);
    delay(1000);
    lcd.clearScreen();
    lcd.setText(0, 0, "Enter The Profile");
    lcd.setText(0, 35, "Info In WebPage:");
    lcd.setText(0, 70, "http://" + connection.ip.toString());
    lcd.setText(0, 105, "WiFiName:" + String(ssid));
    lcd.setText(0, 140, "Pass:" + String(password));
    delay(2000);

    // Check if all data are saved
    connection.checkOneTimeSetup();
    lcd.clearScreen();
    lcd.setText(0, 0, "Successfully Saved");
    lcd.setText(0, 35, "Patient Profile");
    Serial.print(connection.readAllData());
    delay(1000);
    lcd.clearScreen();

    setPage.heartRatePage(lcd);
    heart.pox.update();
    heart.pox.shutdown();
    heart.pox.resume();
    heart.pox.update();
    heart.pox.begin();
}

void loop()
{

    if (int(heart.readHeartRate()))
        lastHarRate = heart.readHeartRate();
    if (int(heart.readOxygenSaturation()))
        lastSpo2 = heart.readOxygenSaturation();

    setPage.statePageValues(lcd,
                            state.checkHeartRate((connection.readFromSD("age").toInt()), lastHarRate),
                            state.checkBloodOxygen((connection.readFromSD("age").toInt()), lastSpo2),
                            state.checkBloodPressure((connection.readFromSD("age").toInt()), connection.readFromSD("gender")),
                            lastHarRate, lastSpo2);

    setPage.heartRatePageValues(lcd, heart, moving, temp);
}
