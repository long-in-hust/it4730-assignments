#include "projectlib.h"

const String serverPrefix = "postman-echo.com";
WiFiClient client;

void httpGetFunction1() {
  Serial.println("--- HTTP GET - using urlencoded data ---\n\n");

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, serverPrefix);
    int returnCode = http.get("/get");
    if (returnCode == 0) {
      Serial.print("Response Status Code: ");
      Serial.println(http.responseStatusCode());
      Serial.printf("Response Body: ");
      Serial.println(http.responseBody());
    }
  }
}