#include "dhtFunctions.h"

// WiFiClient client;

void printDht(String temp, String hum, LiquidCrystal_I2C display) {
  display.clear();

  String messageTemp = "Temp: " + temp;
  String messageHum = "Hum: " + hum;

  Serial.println(messageTemp);
  display.setCursor(0, 0);
  display.print(messageTemp);
  
  Serial.println(messageHum);
  display.setCursor(0, 1);
  display.print(messageHum);
}
