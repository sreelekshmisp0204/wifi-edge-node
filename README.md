# WiFi Edge Node

## Project

WiFi-based edge telemetry node for polyhouse mushroom cultivation.

## Purpose

Collect environmental data such as:

- Temperature
- Humidity
- CO₂

and transmit the data to cloud services for monitoring and analysis.

## Hardware

Board: ESP8266 (ESP-12F)

## Reason for Selection

The ESP8266 was selected because:

- It provides built-in WiFi connectivity.
- It is low-cost and widely available.
- It consumes relatively low power.
- It is suitable for simple sensor-monitoring applications.
- It offers sufficient performance for transmitting environmental data to cloud platforms.

## Future Sensors

- DHT22 Temperature and Humidity Sensor
- CO₂ Sensor (to be added in later stages)

## Repository Structure

wifi-edge-node/
├── src/
├── include/
├── data/
├── docs/
└── README.md

## Application

This edge node will be deployed in a polyhouse mushroom cultivation environment to monitor environmental conditions and send telemetry data to the cloud for remote supervision.
