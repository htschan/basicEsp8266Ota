# Basic project template for ESP8266 with OTA

This work is derived from https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/


# Features

- Over-the-air updates of Firmware
- Upload files for SPIFF
- Basic Authentication for OTA
- Using one asynchronous Task to monitor a digital input


# Environment

## Hostmachine

- Ubuntu 22.04.1 LTS  (jammy)
- Visual Studio Code 1.74.2 (Nov 2022)
- PlatformIO 2.5.5 (VS Code Extension)

## Target 

- CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/esp32dev.html
- PLATFORM: Espressif 32 (5.3.0) > Espressif ESP32 Dev Module
- HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash

## Library dependencies

- me-no-dev/ESPAsyncTCP@^1.2.2
- me-no-dev/ESP Async WebServer@^1.2.3
- ayushsharma82/AsyncElegantOTA@^2.2.7

# Private Data

There should be a file `private_data.h` be placed in the `inlcude` folder cotaining your private credentials:

```
#undef myOTAUSER
#undef myOTAPASSWORD
#undef mySSID
#undef myPASSWORD
#define myOTAUSER "theOTAuser"
#define myOTAPASSWORD "theOTApassword"
#define mySSID "theSSID"
#define myPASSWORD "theSSIDpassword"
```