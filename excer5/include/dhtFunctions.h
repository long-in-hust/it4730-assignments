#ifndef DHTFUNCTIONS_H
#define DHTFUNCTIONS_H

#include "projectlib.h"

void printDht(String temp, String hum, LiquidCrystal_I2C display);
void sendDhtGet(String temp, String hum);
void sendDhtPostUrl(String temp, String hum);
void sendDhtPostBody(String temp, String hum);

#endif