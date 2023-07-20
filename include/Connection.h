#ifndef CONNECTION_H
#define CONNECTION_H

#ifndef __ARDUINO_H
#define __ARDUINO_H
#include <Arduino.h>
#endif

#ifndef __SCREENDISPLAY_H
#define __SCREENDISPLAY_H
#include "ScreenDisplay.h"
#endif
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Preferences.h>
#include <DNSServer.h>

class Connection
{
private:
    AsyncWebServer server;
    Preferences preferences;
    const char *ssid;
    const char *password;
     
    void setupAP(ScreenDisplay &lcd);
    void setupWIFI(ScreenDisplay &lcd);
    void setupServer();
    

public:
    const char* hostname = "patient";
    IPAddress ip;
    Connection(const char *, const char *);
    void setup(ScreenDisplay &lcd, bool isAccessPoint = true);
    void writeData(AsyncWebServerRequest *request);
    String readFromSD(const char *key);
    String readAllData();
    void removeAllData(AsyncWebServerRequest *request);
    void checkOneTimeSetup();
};

#endif