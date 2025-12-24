#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

#include "projectlib.h"
#define LEDPIN 38

boolean mqttConnected(PubSubClient &client, const char * server);
void mqttPublish(PubSubClient &client, dht_data data);
void mqttCallback(char *topic, byte *payload, unsigned int length);

#endif
