#include <Arduino.h>
#include "DetectMoving.h"
#include "LiquidCrystal.h"


// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

DetectMoving moving;


void setup(){

  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  moving.setup();

}

void loop(){

  moving.detectMoving();





}