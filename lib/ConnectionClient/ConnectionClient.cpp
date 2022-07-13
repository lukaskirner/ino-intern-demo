#include "ConnectionClient.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

bool ConnectionClient::connectToWiFi(const char *ssid, const char *password)
{
    Serial.printf("Attempting to connect to AP %s", ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.printf("\nEstablished connection to AP %s\n", ssid);
    return true;
}

PubSubClient *ConnectionClient::initMQTTClient(const char *host, const int port, const char *clientId)
{
    Serial.printf("Attempting to connect to the MQTT broker: %s:%i ...\n", host, port);

    mqttClient.setServer(host, port);
    if (!mqttClient.connect(clientId))
    {
        Serial.printf("MQTT connection failed with state: %i\n", mqttClient.state());
        return nullptr;
    }

    Serial.printf("Established connection to MQTT Broker: %s:%i\n", host, port);
    return &mqttClient;
}

/**
    -4 : MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time
    -3 : MQTT_CONNECTION_LOST - the network connection was broken
    -2 : MQTT_CONNECT_FAILED - the network connection failed
    -1 : MQTT_DISCONNECTED - the client is disconnected cleanly
    0 : MQTT_CONNECTED - the client is connected
    1 : MQTT_CONNECT_BAD_PROTOCOL - the server doesn't support the requested version of MQTT
    2 : MQTT_CONNECT_BAD_CLIENT_ID - the server rejected the client identifier
    3 : MQTT_CONNECT_UNAVAILABLE - the server was unable to accept the connection
    4 : MQTT_CONNECT_BAD_CREDENTIALS - the username/password were rejected
    5 : MQTT_CONNECT_UNAUTHORIZED - the client was not authorized to connect
 */