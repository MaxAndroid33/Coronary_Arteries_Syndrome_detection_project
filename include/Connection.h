#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Preferences.h>




class Connection
{
private:
    IPAddress ip;
    AsyncWebServer server;
    Preferences preferences;
    const char *ssid;
    const char *password;
    String index;

    void setupAP();
    void setupWIFI();
    void setupServer();

public:
    Connection(const char *, const char *);
    void setup(bool isAccessPoint = true);
    void writeData(AsyncWebServerRequest *request);
    String readFromSD(const char * key);
    String readAllData();
    void removeAllData(AsyncWebServerRequest *request);
    void checkOneTimeSetup();

};

#endif