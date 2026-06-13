#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <DHT.h>

// ===== DHT22 =====
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// ===== WiFi =====
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ===== Zelbytes API =====
const char* apiKey = "YOUR_API_KEY";
const char* serverURL =
"https://careers.zelbytes.com/api/iot-lab/v1/telemetry";

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  Serial.println("Starting...");

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
    Serial.println("DHT22 Read Failed!");
    delay(5000);
    return;
  }

  WiFiClientSecure client;
  client.setInsecure();   // Skip certificate validation

  HTTPClient https;

  if (https.begin(client, serverURL)) {

    https.addHeader("Content-Type", "application/json");
    https.addHeader("X-Iot-Lab-Key", apiKey);

    String payload = "{";
    payload += "\"temperature_c\":" + String(temperature, 1) + ",";
    payload += "\"humidity_pct\":" + String(humidity, 1) + ",";
    payload += "\"soil_moisture_pct\":0,";
    payload += "\"co2_ppm\":0";
    payload += "}";

    Serial.println("Sending:");
    Serial.println(payload);

    int httpResponseCode = https.POST(payload);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.println(response);
    } else {
      Serial.println("Error sending request");
    }

    https.end();
  }

  delay(30000); // Send every 30 seconds
}
