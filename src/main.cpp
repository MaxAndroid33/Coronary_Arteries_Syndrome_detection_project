
#include <HeartRate.h>
#include <Connection.h>

const char *ssid = "root";
const char *password = "maxmax123";

Connection connection(ssid, password);
HeartRate heart;

void handleMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {

        data[len] = 0;
        Serial.print("received==>");
        Serial.println((char *)data);

        char *key = strtok((char *)data, ":");
        char *valueStr = strtok(NULL, " ");
        int value = atoi(valueStr);

        if (strcmp(key, "ID") == 0)
        {
        }
    }
}
void updateMsg()
{
    connection.broadcastIP();
    connection.broadcastMsg("ID:");
}
// Callback routine is executed when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
}
void setup()
{

    Serial.begin(115200);
    connection.setup(handleMessage);

    heart.setup();
    heart.pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{

    connection.update();
    if ((millis() - connection.interval) > 2000)
    {
        updateMsg();

        connection.interval = millis();
    }
    heart.readHeartRate();
    heart.readOxygenSaturation();
}
