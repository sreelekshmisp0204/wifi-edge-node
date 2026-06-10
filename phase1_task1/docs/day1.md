# Day 1 Documentation

## Board Used
ESP8266 NodeMCU

## Blink Test
Status: Successful

The blink sketch was uploaded successfully and the onboard LED blinked as expected.

## ESP8266 vs ESP32

ESP8266:
- Lower cost
- Built-in WiFi
- Suitable for basic IoT projects

ESP32:
- More RAM
- More GPIO pins
- Bluetooth support
- Better for MQTT + TLS

## DHT22 Pin Mapping

DHT22 VCC  -> 3.3V
DHT22 DATA -> D2 (GPIO4)
DHT22 GND  -> GND

Note:
D2 (GPIO4) is selected as a safe GPIO for DHT22 communication.

## Learning Outcome
Successfully flashed a blink sketch and learned the differences between ESP8266 and ESP32.
