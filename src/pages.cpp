
#include "Pages.h"

int16_t Pages::heartRatePage(ScreenDisplay &lcd)
{
    int16_t w;
    lcd.clearScreen();
    lcd.setText(0, 15, "Body is = ");
    w = lcd.setText(0, 50, "Heart Rate = ");
    lcd.setText(0, 85, "SpO2 = ");
    lcd.setText(0, 120, "Temp(*C) = ");
    this->w = w;
    return w;
}

int16_t Pages::statePage(ScreenDisplay &lcd)
{
    int16_t w;
    lcd.clearScreen();
    lcd.setText(0, 15, "H/R = ");      // 'H/R' means Heart Rate
    w = lcd.setText(0, 50, "BOxy = "); //'BOxy'  means Blood Oxygen
    lcd.setText(0, 85, "BP = ");       //'BP' means means Blood Pressure
    lcd.setText(0, 120, "H/R:");
    lcd.setText(0, 145, "BOxy:");
    this->w = w;
    return w;
}

void Pages::selectPage(ScreenDisplay &lcd)
{

    switch (pageNum)
    {
    case 0:
        w = heartRatePage(lcd);
        break;
    case 1:
        w = statePage(lcd);
        break;
    default:
        lcd.clearScreen();
        break;
    }
}

void Pages::slidePage(ScreenDisplay &lcd)
{

    pageNum++;
    if (pageNum > 1)
        pageNum = 0;
    selectPage(lcd);
}

void Pages::heartRatePageValues(ScreenDisplay &lcd, HeartRate &heart, DetectMoving &moving, TempSensor &temp)
{
    static int x = 0;
    static int y = 0;
    if (pageNum == 0)
    {
        heart.pox.resume();
        heart.pox.update();
        if (x == 0)

            heart.pox.begin();
        x++;
        y = 0;
        String movingState = moving.detectMoving() ? "Moving" : "Not Moving";
        lcd.setText(w + 10, 25, movingState + "                 ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 32, 60, String(heart.readHeartRate()) + "        ", true, 0, 10, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 22, 95, String(heart.readOxygenSaturation()) + "      ", true, 0, 10, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 22, 130, String(temp.readTemperature()) + "      ", true, 0, 10, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
    }
    else
    {
        x = 0;
        heart.pox.update();
        heart.pox.shutdown();

        if (y == 0)
        {
            lcd.clearScreen();
            statePage(lcd);
        }
        y++;
    }
}

void Pages::statePageValues(ScreenDisplay &lcd,  String HR, String SPO2, String BP, float lastHeartRate, float lastSpo2)
{
    static int x = 0;

    if (pageNum == 1)
    {
        x = 0;
        lcd.setText(w + 20, 25, HR, true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 25, 60, SPO2, true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 10, 95, BP, true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 10, 130, String(lastHeartRate) + " B/min       ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
        lcd.setText(w + 15, 160, String(lastSpo2) + " %      ", true, 0, 2, COLOR_WHITE, 2, FreeSans9pt7b, COLOR_BLACK);
    }
    else
    {
        if (x == 0)
        {
            lcd.clearScreen();
            heartRatePage(lcd);
        }
        x++;
    }
}
