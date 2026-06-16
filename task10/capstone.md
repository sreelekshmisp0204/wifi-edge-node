# IoT Polyhouse Monitoring System using ESP32 and DHT22

## 1. Project Overview

This project demonstrates an end-to-end IoT monitoring system using an ESP32 microcontroller and DHT22 temperature-humidity sensor. The ESP32 collects environmental data and transmits it to the Zelbytes IoT Learning Platform using both HTTPS Telemetry and MQTT-style APIs.

The cloud platform stores the received data and provides APIs for visualization, monitoring, and analysis.

---

## 2. Objective

* Read temperature and humidity using DHT22.
* Connect ESP32 to Wi-Fi.
* Send sensor data using HTTPS Telemetry API.
* Publish the same data using MQTT-style API.
* Verify data storage using Zelbytes Read APIs.
* Visualize the collected data through the IoT Lab Dashboard.

---

## 3. Hardware Components Used

| Component                           | Quantity    |
| ----------------------------------- | ----------- |
| ESP32 Development Board             | 1           |
| DHT22 Temperature & Humidity Sensor | 1           |
| USB Cable                           | 1           |
| Breadboard / Jumper Wires           | As Required |
| Wi-Fi Network                       | 1           |

---

## 4. Software Tools Used

* Arduino IDE
* ESP32 Board Package
* DHT Sensor Library
* ArduinoJson Library
* Zelbytes IoT Learning Platform

---


## 5. Working Methodology

### Step 1: Sensor Data Acquisition

The DHT22 sensor continuously measures:

* Temperature (°C)
* Relative Humidity (%)

The ESP32 reads these values periodically.

### Step 2: JSON Payload Creation

The sensor readings are converted into JSON format.

Example:

```json
{
  "device_id": "polyhouse-dht22-esp32",
  "temperature_c": 34.5,
  "humidity_pct": 75.5
}
```

### Step 3: HTTPS Telemetry Upload

The ESP32 sends the JSON payload to:

https://careers.zelbytes.com/api/iot-lab/v1/telemetry

using the X-Iot-Lab-Key authentication header.

### Step 4: MQTT-style Publish

The same sensor data is published to:

https://careers.zelbytes.com/api/iot-lab/v1/mqtt/publish

using topic:

zelbytes/lab/96/telemetry

Example:

```json
{
  "topic": "zelbytes/lab/96/telemetry",
  "payload": "{\"temp_c\":34.5,\"humidity_pct\":75.5}"
}
```

### Step 5: Data Verification

The uploaded data is verified through:

* GET /telemetry/latest
* GET /telemetry/series
* MQTT Message Log

---

## 6. Sample Output

### HTTPS Response

```text
{"status":"accepted","protocol":"HTTPS","id":1137}
```

### MQTT Response

```text
{"status":"published","protocol":"MQTT","message_id":370}
```

---

## 7. Results

* Successfully connected ESP32 to Wi-Fi.
* Successfully interfaced DHT22 sensor.
* Successfully uploaded telemetry data using HTTPS.
* Successfully published telemetry data using MQTT-style API.
* Successfully verified cloud data through API Explorer.
* Dashboard displayed real-time sensor readings.

## 8. Conclusion

The IoT Polyhouse Monitoring System was successfully implemented using ESP32 and DHT22. Sensor readings were transmitted to the Zelbytes IoT Learning Platform through both HTTPS and MQTT-style APIs. The collected data was stored, retrieved, and visualized successfully, demonstrating a complete IoT data acquisition and cloud integration workflow.
