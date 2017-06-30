#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include "settings.h"
#include "mqtt/mqtt.h"
#include "ota/ota.h"
#include "controller.h"
#include "wheel.h"
#include "cutter.h"
#include "bwf.h"
#include "battery.h"
#include "gps.h"

/*
 * Application to control a LIAM robot mower using a NodeMCU/ESP-12E (or similar ESP8266) microcontroller.
 */
MQTT_Client mqtt;
OTA ota(mqtt);
Wheel leftWheel;
Wheel rightWheel;
Cutter cutter;
BWF bwf;
Battery battery;
GPS gps;
Controller controller(mqtt, leftWheel, rightWheel, cutter, bwf, battery, gps);

void setup_WiFi() {
  WiFi.hostname(Definitions::APP_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(Settings::SSID, Settings::WIFI_PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println(Definitions::APP_NAME);

  setup_WiFi();
  mqtt.connect();
}

void loop() {
  ota.handle();

  // ESP.getCycleCount() // "returns the cpu instruction cycle count since start as an unsigned 32-bit."
  // ESP.getFreeHeap() // "returns the free heap size."
}
