#include <WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "Galaxy A14 5G B70F ";
const char* password = "nandanabs";

#define RELAY_PIN 26

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("WiFi Connected");
  Serial.println("Subscribed to zelbytes/bench/95/cmd");
  Serial.println("System Ready");
}

void handleCommand(String payload) {

  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.println("Command received");
    Serial.println("Invalid JSON");
    return;
  }

  String cmd = doc["message"];

  Serial.println("Command received");
  Serial.println(cmd);

  if (cmd == "IRRIGATE") {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Valve OPEN (Relay ON)");
  }

  else if (cmd == "STOP") {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Valve CLOSED (Relay OFF)");
  }

  else {
    Serial.println("UNKNOWN COMMAND");
  }
}

