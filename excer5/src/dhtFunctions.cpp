#include "projectlib.h"

#define I2C_SDA 42
#define I2C_SCL 41
// #define DHTTYPE DHT22
// #define DHTPIN 45

LiquidCrystal_I2C lcd(0x27,16,2);
// DHT dht(DHTPIN, DHTTYPE);

void printDht(float temp, float hum) {
  String messageTemp = "";
  String messageHum = "";
  // float temp = dht.readTemperature();
  // float hum = dht.readHumidity();
  messageTemp = "Temp: " + String(temp, 1);
  messageHum = "Hum: "  + String(hum, 1);

  lcd.setCursor(0, 0);
  lcd.print(messageTemp);

  lcd.setCursor(0, 1);
  lcd.print(messageHum);

}