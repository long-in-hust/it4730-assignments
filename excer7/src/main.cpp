#include <DHT.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_SDA 42
#define I2C_SCL 41
#define DHTTYPE DHT22
#define DHTPIN 45
#define LEDPIN 1
#define PIRPIN 2

String hostThingspeak = "api.thingspeak.com";
String tsPath = "/update.json?api_key=J69MXGIE0KLMA27C";

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void displayDht(const String temp, const String hum, LiquidCrystal_I2C& display);
void sendDht(const String host, String path, const String temp, const String hum);
void loopSendMotion(const String host, String path, void *pvParameters);

void loopMotionLed(void *pvParameters);
void loopDht(void *pvParameters);

void setup() {
  pinMode (LEDPIN, OUTPUT);
  pinMode (PIRPIN, INPUT);
  Serial.begin(115200);
  while (!Serial) {}
  
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();                     
  lcd.backlight();
  Serial.println("\nLCD initialised!");

  dht.begin();
  Serial.println("\nDHT initialised!");

  delay(1000);

  xTaskCreate(
      loopDht, // Function that should be called
      "DHT retriever", // Name of the task (for debugging)
      4096, // Stack size (bytes)
      NULL, // Parameter to pass
      1, // Task priority
      NULL // Task handle
  );

  xTaskCreate(
      loopMotionLed, // Function that should be called
      "Motion detector", // Name of the task (for debugging)
      4096, // Stack size (bytes)
      NULL, // Parameter to pass
      1, // Task priority
      NULL // Task handle
  );
}

void loop() {

}

void displayDht(const String temp, const String hum, LiquidCrystal_I2C& display) {
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

void sendDht(const String host, String path, const String temp, const String hum) {
  Serial.println("--- HTTP GET - using urlencoded data ---\n");

  path += "&field1=" + temp + "&field2=" + hum;

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, host);
    int returnCode = http.get(path);
    if (returnCode == 0) {
      Serial.print("Response Status Code: ");
      Serial.println(http.responseStatusCode());

      Serial.println("\nResponse Body: ");
      Serial.println(http.responseBody());
    }
  }

  Serial.println("--- End of: HTTP GET - using urlencoded data ---\n\n");
}

void sendMotion(const String host, String path, boolean motion) {
  Serial.println("--- HTTP GET - using urlencoded data ---\n");

  path += "&field3=" + String(motion);

  if(WiFi.status()== WL_CONNECTED) {
    HttpClient http(client, host);
    int returnCode = http.get(path);
    if (returnCode == 0) {
      Serial.print("Response Status Code: ");
      Serial.println(http.responseStatusCode());

      Serial.println("\nResponse Body: ");
      Serial.println(http.responseBody());
    }
  }

  Serial.println("--- End of: HTTP GET - using urlencoded data ---\n\n");
}

void loopMotionLed(void *pvParameters) {
  while (1) {
    if (digitalRead(PIRPIN) == HIGH) {
      digitalWrite (LEDPIN, HIGH);
      Serial.println("Motion Detected ! LED is powered ON.");
    }
    else {
      digitalWrite (LEDPIN, LOW);
      Serial.println("NO motion Detected ! LED is powered OFF.");
    }
    sendMotion(hostThingspeak, tsPath, (digitalRead(PIRPIN) == HIGH));

    delay(1000);
    digitalWrite (LEDPIN, LOW);
  }
}

void loopDht(void *pvParameters) {
  while (1) {
    String temp = String(dht.readTemperature(), 1);
    String humd = String(dht.readHumidity(), 1);

    displayDht(temp, humd, lcd);
    sendDht(hostThingspeak, tsPath, temp, humd);

    delay(1000);
  }
}