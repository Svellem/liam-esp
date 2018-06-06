
#ifndef _liam_wifi_h
#define _liam_wifi_h

#include <string>
#include <queue>
#include <ESP32Ticker.h>
#include <Arduino.h>
#include <AsyncMqttClient.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "configuration.h"


struct MQTT_Message {
  std::string message;
  std::string topic;
};

class WiFi_Client {
  public:
    WiFi_Client();
    void start();
    void publish_message(std::string message, std::string subtopic = "");
    AsyncWebServer& getWebServer();  // code-smell, we should think of a better way than to expose this inner reference when we need to register routes!
    void checkWifiSettings();

  private:
    static WiFi_Client* Instance;
    static String renderPlaceholder(const String& placeholder);
    Ticker wifiReconnectTimer;

    AsyncMqttClient mqttClient;
    Ticker mqttReconnectTimer;
    Ticker flushQueueTimer;
    std::queue<MQTT_Message> msgQueue;

    AsyncWebServer web_server;
    static void WiFiEvent(system_event_id_t event, system_event_info_t info);
    bool isMQTT_enabled();
    void flushQueue();
    void connect();
    void onWifiConnect(system_event_id_t event, system_event_info_t info);
    void onWifiDisconnect(system_event_id_t event, system_event_info_t info);
    void connectToMqtt();
    void onMqttConnect(bool sessionPresent);
    void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
    void onMqttPublish(uint16_t packetId);
    void setupWebServer();
};

#endif