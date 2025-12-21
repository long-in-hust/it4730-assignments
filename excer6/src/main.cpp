#include "projectlib.h"
#include "dhtFunctions.h"

#define DHTTYPE DHT22
#define DHTPIN 2
#define I2C_SDA 42
#define I2C_SCL 41

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Wire.setPins(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  while (!Serial) {}

  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  lcd.init();                     
  lcd.backlight();
  Serial.println("\nLCD initialised!");

  dht.begin();
  Serial.println("\nDHT initialised!");

  delay(1000);
}

void loop() {
  String temp = String(dht.readTemperature(), 1);
  String hum = String(dht.readHumidity(), 1);
  printDht(temp, hum, lcd);
  delay(1000);
}