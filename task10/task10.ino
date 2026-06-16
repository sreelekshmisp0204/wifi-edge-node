#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

// -----------------------------
// DHT22 Configuration
// -----------------------------
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// -----------------------------
// WiFi Credentials
// -----------------------------
const char* ssid = "redmi9";
const char* password = "12345678";

// -----------------------------
// Zelbytes API Configuration
// -----------------------------
const char* apiKey = "zil_kqy0hofkazkhp4ncwiy0noxl33pegayc";

const char* telemetryURL =
  "https://careers.zelbytes.com/api/iot-lab/v1/telemetry";

const char* mqttURL =
  "https://careers.zelbytes.com/api/iot-lab/v1/mqtt/publish";

const char* mqttTopic =
  "zelbytes/lab/96/telemetry";   // Use your actual topic

// -----------------------------

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("====================================");
  Serial.println("   Zelbytes Polyhouse Node");
  Serial.println("====================================");

  dht.begin();

  // Connect WiFi
  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

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

  // -----------------------------
  // Read DHT22
  // -----------------------------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT22!");
    delay(5000);
    return;
  }

  // -----------------------------
  // Display Sensor Values
  // -----------------------------
  Serial.println();
  Serial.println("========== SENSOR DATA ==========");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // ==========================================================
  // PHASE 6 : NORMAL HTTPS TELEMETRY
  // ==========================================================

  StaticJsonDocument<200> telemetryDoc;

  telemetryDoc["device_id"] = "polyhouse-dht22-esp32";
  telemetryDoc["temperature_c"] = temperature;
  telemetryDoc["humidity_pct"] = humidity;

  String telemetryJson;
  serializeJson(telemetryDoc, telemetryJson);

  Serial.println();
  Serial.println("Telemetry JSON:");
  Serial.println(telemetryJson);

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;

    if (https.begin(client, telemetryURL)) {

      https.addHeader("Content-Type", "application/json");
      https.addHeader("X-Iot-Lab-Key", apiKey);

      int responseCode = https.POST(telemetryJson);

      Serial.print("HTTPS Response Code: ");
      Serial.println(responseCode);

      if (responseCode > 0) {
        Serial.println("Telemetry Upload Successful");
        Serial.println(https.getString());
      } else {
        Serial.print("Telemetry Upload Failed: ");
        Serial.println(https.errorToString(responseCode));
      }

      https.end();
    }
  }

  // ==========================================================
  // PHASE 7 : MQTT-STYLE PUBLISH
  // ==========================================================

  // Inner MQTT payload
  StaticJsonDocument<100> payloadDoc;
  payloadDoc["temp_c"] = temperature;
  payloadDoc["humidity_pct"] = humidity;

  String payloadString;
  serializeJson(payloadDoc, payloadString);

  // Outer MQTT wrapper
  StaticJsonDocument<256> mqttDoc;
  mqttDoc["topic"] = mqttTopic;
  mqttDoc["payload"] = payloadString;

  String mqttJson;
  serializeJson(mqttDoc, mqttJson);

  Serial.println();
  Serial.println("MQTT JSON:");
  Serial.println(mqttJson);

  if (WiFi.status() == WL_CONNECTED) {

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;

    if (https.begin(client, mqttURL)) {

      https.addHeader("Content-Type", "application/json");
      https.addHeader("X-Iot-Lab-Key", apiKey);

      int mqttResponse = https.POST(mqttJson);

      Serial.print("MQTT-style Response Code: ");
      Serial.println(mqttResponse);

      if (mqttResponse > 0) {
        Serial.println("MQTT Published Successfully!");
        Serial.println(https.getString());
      } else {
        Serial.print("MQTT Publish Failed: ");
        Serial.println(https.errorToString(mqttResponse));
      }

      https.end();
    }
  }

  Serial.println();
  Serial.println("-----------------------------------");
  Serial.println("Waiting 30 seconds...");
  Serial.println("-----------------------------------");

  delay(30000);
}