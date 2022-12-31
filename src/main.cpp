#include <Arduino.h>

// OTA stuff included here
String projectTitle = "ESP8266 OTA project template";
String projectDesc =
    "Inspired by <a href='https://github.com/RalphBacon/228-Wireless-Over-the-Air-OTA-ESP32-updates' target='_blank'>Wireless-Over-the-Air on Github</a>.</p> \
  <p>Note: The project template is here: <a href='https://github.com/htschan/basicEsp8266Ota'>basicEsp8266Ota on Github</a></p>";

#include "ota.h"

// Flashy flashy LED to prove we can change flash rate
#define ledPin 16 // D0 for ESP8266 NodeMCU

void setup()
{
    // Flashy flashy LED for our demo
    pinMode(ledPin, OUTPUT);

    // Everything for OTA updates
    otaInit();
}

// Nothing to see here. No, really.
void loop()
{
    // Variables just for this function
    static unsigned long counter = 1;
    static unsigned long prevMillis = 0;

    // We'll update a counter every few seconds
    if (millis() - prevMillis > 3000)
    {
        printf("Counter is now %ld\n", ++counter);
        prevMillis = millis();
    }

    // We'll flash an LED for n milliseconds
    digitalWrite(ledPin, millis() % 1000 > 975 ? HIGH : LOW);
}
