// Allow OTA software updates
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#include "private_data.h"

// We've  declared the project ID in the main sketch
extern String projectTitle;
extern String projectDesc;

// This is the standard web server for the ESP32 (on port 80)
AsyncWebServer server(80);

// Convert the WiFi (error) response to a string we can understand
const char *wl_status_to_string(wl_status_t status)
{
    switch (status)
    {
    case WL_NO_SHIELD:
        return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:
        return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:
        return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:
        return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:
        return "WL_CONNECTED";
    case WL_CONNECT_FAILED:
        return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:
        return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:
        return "WL_DISCONNECTED";
    default:
        return "UNKNOWN";
    }
}

// This is what me must do to get it all running
void otaInit()
{

    printf("Setting ESP8266 as Station, no power savings, SSID %s\n", SSID);

    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.disconnect(true);
        printf("WiFi was previously connected - now disconnected\n");
    }

    WiFi.mode(WIFI_STA);
    WiFi.persistent(false);
    WiFi.setAutoReconnect(true);
    WiFi.setSleep(false);

    if (WiFi.begin(SSID, PASSWORD))
    {
        printf("WiFi begin success.\n");
    }
    // WiFi.setTxPower(WIFI_POWER_5dBm);
    delay(2000);

    printf("Connecting to WiFi .");
    uint8_t wifiStatus = WiFi.waitForConnectResult();

    // Successful connection?
    if ((wl_status_t)wifiStatus != WL_CONNECTED)
    {
        printf("WiFi Status: %s, exiting\n", wl_status_to_string((wl_status_t)wifiStatus));
        while (1)
            ;
    }

    // Just some information about the Wifi
    printf(
        "\nRunning on SSID %s with IP %s, Channel %d, MAC address %s\n",
        (char *)WiFi.SSID().c_str(),
        (char *)(WiFi.localIP()).toString().c_str(),
        WiFi.channel(),
        (char *)WiFi.macAddress().c_str());

    // This gets printed when you type the IP address followed by /whoami
    server.on("/whoami", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", projectDesc); });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  printf("Sending response started\n");
                  request->send(
                      200,
                      "text/html",
                      R"(
        <!DOCTYPE HTML>
        <head><title>)" +
                          String(projectTitle) +
                          R"(</title></head>
        <body style='font-size:1.1em;'>
          <h3>ESP8266 OTA Home Page</h3>
          <div>Congratulations! You've reached your )" +
                          String(projectTitle) +
                          R"( 8266 device on IP )" +
                          String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(</div>
         <fieldset style="margin:20px 5px 20px 5px;border:1px;border-radius:5px;border:1px solid darkgray;background-color:white">
          <legend style="font-size:0.8em;">Project description:</legend>
            <div style="font-size:0.8em;background-color:#EEEEEE;padding:5px;border-radius:10px;">)" +
                          String(projectDesc) +
                          R"(</div>
          </fieldset>
          
          <p> To update your code type this into your address bar:<br /> 
            <a href='http://)" +
                          String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(/update' target='_blank'>http://)" + String((char *)(WiFi.localIP()).toString().c_str()) +
                          R"(/update</a> <br />
            or just click this link.
          </p>
        </body>
        </html>
      )");
                  printf("Sending response ends\n"); });

    // Starting Async OTA web server
    AsyncElegantOTA.begin(&server, OTAUSER, OTAPASSWORD);
    server.begin();
}
