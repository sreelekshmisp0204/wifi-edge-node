
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

const char* ssid = "ruth";
const char* password = "09200509";

const char* apiKey = "zil_dt7gdz2enmfcriik0fsywi4k8fyir5u8";

const char* telemetryUrl =
"https://careers.zelbytes.com/api/iot-lab/v1/telemetry";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT Read Failed!");
    delay(5000);
    return;
  }

  Serial.println("-------------------");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(telemetryUrl);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Iot-Lab-Key", apiKey);

    String payload = "{";
    payload += "\"temperature_c\":" + String(temperature, 1) + ",";
    payload += "\"humidity_pct\":" + String(humidity, 1) + ",";
    payload += "\"soil_moisture_pct\":0,";
    payload += "\"co2_ppm\":0";
    payload += "}";

    Serial.println("Sending:");
    Serial.println(payload);

    int httpResponseCode = http.POST(payload);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.println("HTTP Request Failed");
    }

    http.end();
  }

  delay(10000);
}
