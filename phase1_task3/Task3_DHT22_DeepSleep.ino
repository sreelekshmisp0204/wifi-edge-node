#include <DHT.h>
#include "esp_sleep.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(115200);
  dht.begin();

  delay(2000);

  float temp = NAN;
  float hum = NAN;
  bool success = false;

  for(int i = 0; i < 3; i++) {

    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if(!isnan(temp) && !isnan(hum)) {
      success = true;
      break;
    }

    delay(1000);
  }

  Serial.print("{\"temp\":");

  if(success)
    Serial.print(temp);
  else
    Serial.print("null");

  Serial.print(",\"humidity\":");

  if(success)
    Serial.print(hum);
  else
    Serial.print("null");

  Serial.print(",\"ok\":");
  Serial.print(success ? "true" : "false");

  Serial.println("}");

  Serial.println("Going to sleep for 30 seconds...");

  esp_sleep_enable_timer_wakeup(30 * 1000000ULL);

  delay(100);

  esp_deep_sleep_start();
}

void loop() {
}