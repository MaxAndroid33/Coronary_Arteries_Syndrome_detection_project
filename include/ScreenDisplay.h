#ifndef __SCREENDISPLAY_H__
#define __SCREENDISPLAY_H__

#include <Arduino.h>
#include <TFT_22_ILI9225.h>
#include "SPIFFS.h"

#include <../fonts/FreeSans9pt7b.h>
#include <../fonts/FreeSans12pt7b.h>
#include <../fonts/FreeSerif9pt7b.h>

#define TFT_RST 26 // IO 26
#define TFT_RS 25  // IO 25
#define TFT_CLK 14 // HSPI-SCK
// #define TFT_SDO 12 // HSPI-MISO
#define TFT_SDI 13 // HSPI-MOSI
#define TFT_CS 15  // HSPI-SS0
#define TFT_LED 0  // 0 if wired to +5V directly

#define TFT_BRIGHTNESS 50 // Initial brightness of TFT backlight (optional)

class ScreenDisplay
{
private:
    int16_t x = 0, y = 0, w, h;

public:
    TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_BRIGHTNESS);

    int orientation();
    void displaySetup(String message);
    void displayHeartRate(float heartRateValue);
    void displaySpO2(float spo2Value);
    void clearScreen();

    int16_t setText(int16_t xr, int16_t yr, String txt, bool box = true, int16_t horizontalSpace = 0, int16_t space = 20, int16_t txtColor = COLOR_BLACK, int16_t borderSize = 2, const GFXfont font = FreeSans9pt7b, int16_t boxColor = COLOR_GRAY, int16_t borderColor = COLOR_BLACK); // Use to set text(print) or box in the illi9225 lcd screen
    void setup(SPIClass &hspi);
};

#endif // __SCREENDISPLAY_H__