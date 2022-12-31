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

[env:nodemcuv2]
platform = espressif8266
board = nodemcuv2
framework = arduino

## Library dependencies

- me-no-dev/ESP Async WebServer@^1.2.3
- ayushsharma82/AsyncElegantOTA@^2.2.7
- me-no-dev/ESPAsyncTCP@^1.2.2


# Private Data

There should be a file `private_data.h` be placed in the `inlcude` folder cotaining your private credentials:

```
const char *OTAUSER = "the OTA user";
const char *OTAPASSWORD = "the OTA password";

// WiFi Server stuff and WiFi logon Credentials
const char *SSID = "the WIFI SSID";
const char *PASSWORD = "the WIFI password";
```