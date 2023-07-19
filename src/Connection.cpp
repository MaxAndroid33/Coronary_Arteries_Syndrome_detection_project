#include <Connection.h>
#include <AsyncElegantOTA.h>
#include "index.h"
Connection::Connection(const char *ss, const char *pass) : ssid(ss),
                                                           password(pass),
                                                           server(80)

{
    
}

void Connection::setupAP()
{
    WiFi.softAP(ssid, password);
    ip = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(ip);
}

void Connection::setupWIFI()
{
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
     ip = WiFi.localIP();

    Serial.print("IP address: ");
    Serial.println(ip);
}

void Connection::setupServer()
{

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", index_html); });

    server.on("/save", HTTP_POST, [this](AsyncWebServerRequest *request)
              { writeData(request); });
    server.on("/remove", HTTP_POST, [this](AsyncWebServerRequest *request)
              { removeAllData(request); });
    server.onNotFound([](AsyncWebServerRequest *request)
                      {
        String nfmsg = "Not found\n\n";
        request->send(200, "text/plain", nfmsg); });
    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();
    preferences.begin("AllData", false);
}

void Connection::setup(bool isAccessPoint)
{
    if (isAccessPoint)
    {
        setupAP();
    }
    else
    {
        setupWIFI();
    }
    setupServer();
}

void Connection::writeData(AsyncWebServerRequest *request)
{
    if (request->hasParam("id", true))
    {
        preferences.putString("id", request->getParam("id", true)->value());
        preferences.putString("gender", request->getParam("gender", true)->value());
        preferences.putString("age", request->getParam("age", true)->value());
        preferences.putString("date", request->getParam("date", true)->value());
        preferences.putString("DSP", request->getParam("DSP", true)->value());
        preferences.putString("NHR", request->getParam("NHR", true)->value());
        preferences.putString("SBP", request->getParam("SBP", true)->value());
        preferences.putString("NBT", request->getParam("NBT", true)->value());
        preferences.putString("NSPO", request->getParam("NSPO", true)->value());
        preferences.putString("chol", request->hasParam("chol", true) ? "Yes" : "No");
        preferences.putString("hyper", request->hasParam("hyper", true) ? "Yes" : "No");
        preferences.putString("diabetes", request->hasParam("diabetes", true) ? "Yes" : "No");
        preferences.putString("overw", request->hasParam("overw", true) ? "Yes" : "No");
        preferences.putString("smok", request->hasParam("smok", true) ? "Yes" : "No");
        preferences.putString("alcoh", request->hasParam("alcoh", true) ? "Yes" : "No");
    }
    // Close the Preferences
    preferences.end();
    request->send(200, "text/plain", "Values saved successfully!");
    // Wait 10 seconds
    Serial.println("Restarting in 10 seconds...");
    delay(10000);

    // Restart ESP
    ESP.restart();
}

String Connection::readFromSD(const char *key)
{
    return preferences.getString(key, "None");
}

String Connection::readAllData()
{
    String all = String("ID :") + readFromSD("id") + String("\n") +
                 String("Gender :") + readFromSD("gender") + String("\n") +
                 String("Age :") + readFromSD("age") + String("\n") +
                 String("Date") + readFromSD("date") + String("\n") +
                 String("DSP :") + readFromSD("DSP") + String("\n") +
                 String("NHR :") + readFromSD("NHR") + String("\n") +
                 String("SBP :") + readFromSD("SBP") + String("\n") +
                 String("NBT :") + readFromSD("NBT") + String("\n") +
                 String("Normal SPO2 :") + readFromSD("NSPO") + String("\n") +
                 String("Cholesterol :") + readFromSD("chol") + String("\n") +
                 String("Hypertension :") + readFromSD("hyper") + String("\n") +
                 String("Diabetes :") + readFromSD("diabetes") + String("\n") +
                 String("OverWight :") + readFromSD("overw") + String("\n") +
                 String("Smoking :") + readFromSD("smok") + String("\n") +
                 String("Alcohol :") + readFromSD("alcoh") + String("\n");
    return all;
}

void Connection::removeAllData(AsyncWebServerRequest *request)
{   request->send(200, "text/plain", "remove All Data !!! <br> Restarting in 10 seconds...");
    preferences.clear();
    Serial.println("Restarting in 10 seconds...");
    delay(10000);

    // Restart ESP
    ESP.restart();
}

void Connection::checkOneTimeSetup()
{   String check = readFromSD("id");
    while( check== "None"){
        Serial.println("You Have To Setup Profile First !!!");
    }
}
