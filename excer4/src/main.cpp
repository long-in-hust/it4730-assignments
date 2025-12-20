#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define I2C_SDA 42
#define I2C_SCL 41
#define DHTTYPE DHT22
#define DHTPIN 45
#define LEDPIN 1
#define PIRPIN 2

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);

String messageTemp = "";
String messageHum = "";

void loopBlinkLed(void *pvParameters);
void loopPrintDht(void *pvParameters);
void scroll(int row, String message, int delayTime);

void setup() {
  pinMode (LEDPIN, OUTPUT);
  pinMode (PIRPIN, INPUT);
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  dht.begin();

  xTaskCreatePinnedToCore(loopBlinkLed, "BlinkLed", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(loopPrintDht, "PrintDht", 4096, NULL, 1, NULL, 0);
}

void loop() {}

void loopPrintDht(void *pvParameters) {
  while (1) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    messageTemp = "Temp: " + String(temp, 1);
    messageHum = "Hum: "  + String(hum, 1);

    lcd.setCursor(0, 0);
    lcd.print(messageTemp);

    lcd.setCursor(0, 1);
    lcd.print(messageHum);

    delay(1000);
  }
}

void loopBlinkLed(void *pvParameters) {
  while (1) {
    if (digitalRead(PIRPIN) == HIGH) {
      digitalWrite (LEDPIN, HIGH);
      printf("Motion Detected ! LED is powered ON\n");
      delay(1000);
    }
    if (digitalRead(PIRPIN) == LOW) {
      digitalWrite (LEDPIN, LOW);
      // printf("NO motion Detected ! LED is powered OFF\n");
    }
    
    digitalWrite (LEDPIN, LOW);
  }
}