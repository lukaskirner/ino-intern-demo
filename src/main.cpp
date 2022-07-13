#include <Arduino.h>
#include <ConnectionClient.h>
#include "wifi_secrets.h"

String wifiSSID = SECRET_SSID;
String wifiPassword = SECRET_PASS;

PubSubClient *client;

void callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  // Initialize serial.
  Serial.begin(9600);

  // Establish connection to MQTT Broker by using built-in Wi-Fi.
  ConnectionClient connectionClient;
  connectionClient.connectToWiFi(wifiSSID.c_str(), wifiPassword.c_str());
  client = connectionClient.initMQTTClient("broker.hivemq.com", 1883, "ino-intern-client");
  client->setCallback(callback);

  if (!client->subscribe("ino/intern/iot/led/#"))
  {
    Serial.println("MQTT subscription failed!");
    delay(1000);
  }
  Serial.println("MQTT subscribe successfully");

  // put your setup code here, to run once:
}

void loop()
{
  client->loop();
  // put your main code here, to run repeatedly:
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.printf("Message arrived on topic %s\n", topic);
}