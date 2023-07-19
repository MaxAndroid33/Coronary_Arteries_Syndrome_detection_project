
#include <HeartRate.h>
#include <Connection.h>

const char *ssid = "root";
const char *password = "maxmax123";

Connection connection(ssid, password);
HeartRate heart;


// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
}
void setup()
{

    Serial.begin(115200);
    connection.setup(false);
    Serial.print(connection.readAllData());
    connection.checkOneTimeSetup();
    Serial.print(connection.readAllData());
    // heart.setup();
    // heart.pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
    

    // heart.readHeartRate();
    // heart.readOxygenSaturation();
}
