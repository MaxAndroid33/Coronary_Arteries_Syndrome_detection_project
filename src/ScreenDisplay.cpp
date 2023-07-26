#include "ScreenDisplay.h"

void ScreenDisplay::setup(SPIClass &hspi)
{
    hspi.begin();
    tft.begin(hspi);

    
}
void ScreenDisplay::displaySetup(String message)
{
    setText(50, 50, message);
}

void ScreenDisplay::displayHeartRate(float heartRateValue)
{
    String hR = "Heart Rate = " + String(heartRateValue);
    setText(20, 50, hR);
}

void ScreenDisplay::displaySpO2(float spo2Value)
{
    String sp = "SpO2 = " + String(spo2Value);
    setText(20, 85, sp);
}

void ScreenDisplay::clearScreen()
{
        tft.clear();
}

int16_t ScreenDisplay::setText(int16_t xr, int16_t yr, String txt, bool box, int16_t horizontalSpace, int16_t space, int16_t txtColor, int16_t borderSize, const GFXfont font, int16_t boxColor, int16_t borderColor)
{
    int16_t wr, hr;

    if (box)
    {
        tft.setGFXFont(&font);                   // Set current font
        tft.getGFXTextExtent(txt, x, y, &w, &h); // Get string extents
        wr = w * 1.15 + space - 10 + horizontalSpace;
        hr = h + space;

        tft.fillRectangle(xr, yr, xr + wr, yr + hr, borderColor);                                                  //(x1,y1,x2,y2,color)
        tft.fillRectangle(xr + borderSize, yr + borderSize, xr + wr - borderSize, yr + hr - borderSize, boxColor); //(x1,y1,x2,y2,color)

        x = xr + (wr - w) / 2 - w * 0.05;
        y = yr + (hr / 2) + 2 * borderSize;   // Set y position to string height
        tft.drawGFXText(x, y, txt, txtColor); // Print string
    }
    else
    {
        tft.setGFXFont(&font);                     // Set current font
        tft.getGFXTextExtent(txt, xr, yr, &w, &h); // Get string extents
        tft.drawGFXText(xr, yr, txt, txtColor);    // Print string
    }

    return w;
}
