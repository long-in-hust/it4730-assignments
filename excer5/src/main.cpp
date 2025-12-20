#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>

const String serverPrefix = "postman-echo.com";
WiFiClient client;

void httpGetFunction1();

void setup() {
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    printf(".");
  }
  printf("\nConnected!\n");

  delay(1000);

  httpGetFunction1();
}

void loop() {
  delay(100);
}

void httpGetFunction1() {
  printf("--- HTTP GET - using urlencoded data ---\n\n");

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, serverPrefix);
    int returnCode = http.get("/get");
    if (returnCode == 0) {
      printf("Response Status Code: %d\n", http.responseStatusCode());
      printf("Response Body: \n%s\n", http.responseBody());
    }
  }
}