#include "projectlib.h"

#define DHTTYPE DHT22
#define DHTPIN 45

void httpGetFunction1();
void printDht(String temp, String hum);
void sendDht(String temp, String hum);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  delay(1000);
}

void loop() {
  String temp = String(dht.readTemperature(), 1);
  String hum = String(dht.readHumidity(), 1);
  printDht(temp, hum);
  delay(1000);
}