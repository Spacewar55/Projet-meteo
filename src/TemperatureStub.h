/**
    Gestion de la température (STUB)
    @file TemperatureStub.h
    @author Alex De Souza
    @version 1.0 17/02/23  
*/

#include <Arduino.h>

#ifndef TEMPERATURE_STUB_H
#define TEMPERATURE_STUB_H
#include "DHT.h"
using namespace std;

class TemperatureStub  {
    public:
        void init(int _inputPinUsed = 15, int _typeSensorUsed = DHT11);
        ////0 : Celcius   1:Far
        bool setUniteUsed(int _UniteUsed = 0);
        //Retourne la température su senseur
        float getTemperature();
        //Retourne l'humidité du senseur
        float getHumidite();

    private :     
        // Ici on utilise la pin 15 de l'ESP32
        int inputPinUsed =  15;
        int typeSensorUsed =  DHT22;
        int UniteUsed = 0; //0 : Celcius   1:Far
        DHT *dht = NULL;
        float lastTemperatureRead = -999;
        float lastHumiditeRead = -999;    
};
#endif