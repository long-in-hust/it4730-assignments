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

void sendDhtGet(String temp, String hum) {
  Serial.println("--- HTTP GET - using urlencoded data ---\n");

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

  Serial.println("--- End of: HTTP GET - using urlencoded data ---\n\n");
}

void sendDhtPostUrl(String temp, String hum) {
  Serial.println("--- HTTP POST - using urlencoded data ---\n");

  String path = "/post?temperature=" + temp + "&humidity=" + hum;

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, serverPrefix);
    int returnCode = http.post(path);
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

  Serial.println("--- End of: HTTP POST - using urlencoded data ---\n\n");
}

void sendDhtPostBody(String temp, String hum) {
  Serial.println("--- HTTP POST - using JSON request body ---\n");

  String path = "/post";
  JsonDocument doc;
  doc["temperature"] = temp;
  doc["humidity"] = hum;
  String body = "";
  serializeJson(doc, body);

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, serverPrefix);
    int returnCode = http.post(path, "application/json", body);
    if (returnCode == 0) {
      Serial.print("Response Status Code: ");
      Serial.println(http.responseStatusCode());
      
      deserializeJson(doc, http.responseBody());
      String prettyPayload = "";
      serializeJsonPretty(doc, prettyPayload);

      Serial.printf("Response Body: ");
      Serial.println(prettyPayload);
    }
  }

  Serial.println("--- End of: HTTP POST - using JSON request body ---\n\n");
}