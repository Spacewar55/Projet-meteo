/**
    Gestion de la température (STUB)
    @file main.cpp
    @author Alex De Souza
    @version 1.0 17/02/23  
*/

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
float temperatureDeLaStation = 20;
float humiditeDeLaStation = 20;

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

//Variables pour la connection Wifi
const char *SSID = "METEO_FYPC";
const char *PASSWORD = "meteo_TWVF";

void setup() {
  Serial.begin(9600);

  char strToPrint[128];
  sprintf(strToPrint, "Identification : %s   MotDePasse: %s", SSID, PASSWORD);
  Serial.println(strToPrint);

  if (!wm.autoConnect(SSID, PASSWORD)) {
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
  bool topicTemperature = topic_publish.publish(
    temperatureDeLaStation = temperatureStub->getTemperature()
  );
  bool topicHumidite = topic_publish.publish(
    humiditeDeLaStation = temperatureStub->getHumidite()
  );
  Serial.println(topicTemperature);
  Serial.println(topicHumidite);
  delay(3000);
}