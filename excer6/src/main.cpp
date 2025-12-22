#include "projectlib.h"
#include "dhtFunctions.h"
#include "mqttFunctions.h"

#define DHTTYPE DHT22
#define DHTPIN 2
#define I2C_SDA 42
#define I2C_SCL 41

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
WiFiClient espClient;
PubSubClient psClient(espClient);

const char* brokerHost = "broker.emqx.io";

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

  psClient.setServer(brokerHost, 1883);

  delay(1000);
}

void loop() {
  // Get DHT22 data
  dht_data data;
  data.temp = dht.readTemperature();
  data.humd = dht.readHumidity();

  // Print DHT22 data to LCD
  printDht(
    String(data.temp, 1),
    String(data.humd, 1),
    lcd
  );

  if (mqttConnected(psClient, brokerHost)) {
    mqttPublish(psClient, data);
  }

  delay(1000);
}