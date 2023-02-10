#include <Arduino.h>
#include <ArduinoJson.h>
#include <iostream>
#include <Wire.h>
#include <String>
#include "myFunctions.cpp" //Fonctions utilitaires
#include <HTTPClient.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

using namespace std;

//Initialisation senseur de température
#include "TemperatureStub.h"
#define DHTPIN  15  // Pin utilisée par le DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé
TemperatureStub *temperatureStub = NULL;

//Récupération de la température
float temperatureDuFour = 20;

#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

//Adresse MQTT
const char *mqttServer = "172.16.5.100";
const char *mqttUsername = "mams";
const char *mqttPassword = "mams";
const int mqttPort = 1883;

WiFiClient client;

// Create an instance of the Adafruit MQTT client
Adafruit_MQTT_Client mqtt(&client, mqttServer, mqttPort, mqttUsername, mqttPassword);

// Create a MQTT topic for publishing
Adafruit_MQTT_Publish topic_publish = Adafruit_MQTT_Publish(&mqtt, "test");

//Variable pour la connection Wifi
const char *SSID = "METEO_";
const char *PASSWORD = "meteo_";
String ssIDRandom;

void setup() {
  Serial.begin(9600);
  
  //Connection au WifiManager
  String ssIDRandom, PASSRandom;
  String stringRandom;
  stringRandom = get_random_string(4).c_str();
  ssIDRandom = SSID;
  ssIDRandom = ssIDRandom + stringRandom;
  stringRandom = get_random_string(4).c_str();
  PASSRandom = PASSWORD;
  PASSRandom = PASSRandom + stringRandom;

  char strToPrint[128];
  sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
  Serial.println(strToPrint);

  if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())) {
    Serial.println("Erreur de connexion.");

  } else {
    Serial.println("Connexion Établie.");
  }

  // Connect to the MQTT broker
  if (mqtt.connected()) {
    mqtt.disconnect();
  }

  if (mqtt.connect()) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Could not connect to MQTT broker. Retrying...");

  }

  //Initiation du senseur de température
  temperatureStub = new TemperatureStub;
  temperatureStub->init(DHTPIN, DHTTYPE);
}

void loop() {
  // temperatureDuFour = temperatureStub->getTemperature();
  // Serial.print("Température : ");
  // Serial.println(temperatureDuFour);
  bool topicTemperature = topic_publish.publish(
    temperatureDuFour = temperatureStub->getTemperature()
  );
  Serial.println(topicTemperature);
  delay(3000);
}