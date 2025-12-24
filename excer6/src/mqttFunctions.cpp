#include "mqttFunctions.h"

boolean mqttConnected(PubSubClient &client, const char * server)
{
    if (client.connected())
        return true;

    // Loop until we're reconnected or give up after 5 retries
    int8_t retries = 0;
    while (!client.connected() && retries < 5)
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESPL1057-202512";
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("Successfully connected to the MQTT broker" + (String)server + ". Client ID: " + clientId);
            return true;
        }
        else
        {
            retries++;
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
    Serial.print("Failed to connect to the MQTT broker. Will try again on the next ESP loop.");
    return false;
}

void mqttPublish(PubSubClient &client, dht_data data) {
    String message = "Temp: " + String(data.temp, 1) + "C\tHumd: " + String(data.humd, 1) + "%";
    client.publish("LongLong1057IT", message.c_str());
    Serial.println("Published to topic \"LongLong1057IT\".");
}

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.println("Message arrived [" + String (topic) + "]:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1')
    {
        digitalWrite(LEDPIN, HIGH);
        delay(1000);
    }
    else
    {
        digitalWrite(LEDPIN, LOW);
        delay(1000);
    }
}