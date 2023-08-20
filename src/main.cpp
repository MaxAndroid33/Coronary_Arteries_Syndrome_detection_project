#include "ScreenDisplay.h"
#include <TFT_22_ILI9225.h>
#include "HeartRate.h"
#include "Connection.h"
#include "DetectMoving.h"
#include "StatePerson.h"
#include "Pages.h"
#include "TempSensor.h"

#define SELECT_PAGE_PIN_BTN 27
#define START_BLOOD_PIN_BTN 5

const char *ssid = "root";
const char *password = "maxmax123";
String DoctorNumber = "+96777731173";
Connection connection(ssid, password);
SPIClass hspi(HSPI);

ScreenDisplay lcd;
HeartRate heart;
DetectMoving moving;
StatePerson state;
Pages setPage;
TempSensor temp(4);
int16_t w;
int onceSlide = 0;
float lastHarRate = 0.0, lastSpo2 = 0.0;
SoftwareSerial mySerial(1, 3); //(rx, tx)
int count = 0;
bool readtemp=false;
// Define the time interval in milliseconds (10 hours)
const unsigned long interval = 10UL * 60UL * 60UL * 1000UL;
// Timer variables
unsigned long previousMillis = 0;

void slidePage()
{
  readtemp=!readtemp; 
  lcd.clearScreen();
  setPage.slidePage(lcd);
  if (state.dangerLevel <= 2)
    count = 1;
}
void pressureRead()
{
  digitalWrite(START_BLOOD_PIN_BTN, HIGH);
  delay(1000);
  digitalWrite(START_BLOOD_PIN_BTN, LOW);
}
void setup()
{
 
  // // Initialize All Sensors
  Serial.begin(115200);
  state.begin(mySerial);

  attachInterrupt(digitalPinToInterrupt(SELECT_PAGE_PIN_BTN), slidePage, RISING);

  lcd.setup(hspi);
  lcd.tft.setOrientation(3);
  lcd.clearScreen();
  // Temperature Setup Sensor
  temp.begin();
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
   pinMode(START_BLOOD_PIN_BTN, OUTPUT);
  digitalWrite(START_BLOOD_PIN_BTN, LOW);
  setPage.heartRatePage(lcd);
  heart.pox.update();
  heart.pox.shutdown();
  heart.pox.resume();
  heart.pox.update();
  heart.pox.begin();
  temp.readTemperature();
}

void loop()
{ 
    if(readtemp){ temp.readTemperature();}
    state.testBody(state.checkBloodPressure((connection.readFromSD("age").toInt()), connection.readFromSD("gender")),
                   state.checkHeartRate((connection.readFromSD("age").toInt()), lastHarRate), temp.checkTemperatureBody(),
                   state.checkBloodOxygen((connection.readFromSD("age").toInt()), lastSpo2));
    unsigned long currentMillis = millis();
    // Check if it's time to trigger the output
    if (currentMillis - previousMillis >= interval)
    {
      // Save the last time the output was triggered
      previousMillis = currentMillis;
      pressureRead();
    }
  
  if ((connection.readFromSD("Doctor") == "NO"))
  {
    String message = String("Patient ID:") + connection.readFromSD("id");
    // Serial.println("Send To Doctor");
    state.sendSms(message, DoctorNumber, mySerial);
    connection.writeData("Doctor", "YES");
  }
  if (int(heart.readHeartRate()) > 20)
    lastHarRate = heart.readHeartRate();
  if (int(heart.readOxygenSaturation()) > 20)
    lastSpo2 = heart.readOxygenSaturation();

  setPage.statePageValues(lcd,
                          state.checkHeartRate((connection.readFromSD("age").toInt()), lastHarRate),
                          state.checkBloodOxygen((connection.readFromSD("age").toInt()), lastSpo2),
                          state.checkBloodPressure((connection.readFromSD("age").toInt()), connection.readFromSD("gender")),
                          lastHarRate, lastSpo2);

  setPage.heartRatePageValues(lcd, heart, moving, temp);
  if (count == 1)
  {
    state.alertDoctor(DoctorNumber, mySerial);
    state.alert();
    state.dangerLevel = 10;
    count = 0;
  }

  // state.alert();
}
