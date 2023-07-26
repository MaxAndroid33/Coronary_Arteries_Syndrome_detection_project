#include "ScreenDisplay.h"
#include <TFT_22_ILI9225.h>
#include "HeartRate.h"
#include "Connection.h"
#include "DetectMoving.h"
#include "StatePerson.h"
#include "Pages.h"

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
int16_t w;
// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
    lcd.setText(20, 120, "Beat !!", true, 0, 20, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_RED);
}

void slidePage()
{   lcd.clearScreen();
    setPage.slidePage(lcd);
}
void setup()
{
    // Initialize All Sensors
    Serial.begin(115200);
    attachInterrupt(digitalPinToInterrupt(SELECT_PAGE_PIN_BTN), slidePage, RISING);
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
    lcd.setText(0, 70, "http://"+connection.ip.toString() );
    lcd.setText(0, 140, "WiFiName:"+String(ssid));
    lcd.setText(0, 175, "Pass:"+String(password));
    
    connection.checkOneTimeSetup();
    lcd.clearScreen();
    lcd.setText(0, 0, "Successfully Completed");
    lcd.setText(0 , 35, "Patient Profile");
    delay(3000);
    lcd.clearScreen();
    Serial.print(connection.readAllData());

    
   
    setPage.heartRatePage(lcd);
    heart.pox.update();
    heart.pox.shutdown();
    heart.pox.resume();
   heart.pox.update();
   heart.pox.begin();
   
}

void loop()
{
    // String movingState = moving.detectMoving() ? "Moving" : "Not Moving";
    //     lcd.setText(w + 10, 15, movingState, true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
    //     lcd.setText(w + 30, 50, String(heart.readHeartRate()) + " ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
    //     lcd.setText(w + 20, 85, String(heart.readOxygenSaturation()) + " ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);

    setPage.heartRatePageValues(lcd,heart,moving);
    
    setPage.statePageValues(lcd,heart,
    state.checkHeartRate((connection.readFromSD("age").toInt()), heart.readHeartRate()),
    state.checkBloodOxygen((connection.readFromSD("age").toInt()), heart.readOxygenSaturation()),
    state.checkBloodPressure((connection.readFromSD("age").toInt()), connection.readFromSD("gender")));
    // lcd.setText(w + 30, 50, String(heart.readHeartRate()) + " ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
    // lcd.setText(w + 20, 85, String(heart.readOxygenSaturation()) + " ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
    //    lcd.displaySpO2(heart.readOxygenSaturation());
}
