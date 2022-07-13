#ifndef __CONNECTION_CLIENT_H__
#define __CONNECTION_CLIENT_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <SPI.h>

class ConnectionClient
{
public:
    bool connectToWiFi(const char *ssid, const char *password);
    PubSubClient *initMQTTClient(const char *host, const int port, const char *clientId);
};

#endif