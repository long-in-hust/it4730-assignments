#include "dhtFunctions.h"

const String serverPrefix = "postman-echo.com";
WiFiClient client;

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

void sendDht(String temp, String hum) {
  Serial.println("--- HTTP GET - using urlencoded data ---\n\n");

  String path = "/get?temperature=" + temp + "&humidity=" + hum;

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, serverPrefix);
    int returnCode = http.get(path);
    if (returnCode == 0) {
      Serial.print("Response Status Code: ");
      Serial.println(http.responseStatusCode());
      
      JsonDocument doc;
      deserializeJson(doc, http.responseBody());
      String prettyPayload = "";
      serializeJsonPretty(doc, prettyPayload);

      Serial.printf("Response Body: ");
      Serial.println(prettyPayload);
    }
  }
}