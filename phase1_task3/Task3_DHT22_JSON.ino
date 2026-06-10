#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  delay(2000);
}

void loop() {

  float temp = NAN;
  float hum = NAN;
  bool success = false;

  // Retry up to 3 times
  for (int i = 0; i < 3; i++) {

    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (!isnan(temp) && !isnan(hum)) {
      success = true;
      break;
    }

    delay(1000);
  }

  Serial.print("{\"temp\":");

  if (success)
    Serial.print(temp);
  else
    Serial.print("null");

  Serial.print(",\"humidity\":");

  if (success)
    Serial.print(hum);
  else
    Serial.print("null");

  Serial.print(",\"ok\":");
  Serial.print(success ? "true" : "false");

  Serial.println("}");

  delay(2000);
}