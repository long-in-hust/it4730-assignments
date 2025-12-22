#ifndef PROJECTLIB_H
#define PROJECTLIB_H

#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <PubSubClient.h>

struct dht_data{
  float temp;
  float humd;
};

#endif