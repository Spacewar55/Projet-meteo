/**
    Gestion de la température (STUB)
    @file TemperatureStub.cpp
    @author Alex De Souza
    @version 1.0 17/02/23  
*/

#include "TemperatureStub.h"

void TemperatureStub::init(int _inputPinUsed, int _typeSensorUsed){
    inputPinUsed = _inputPinUsed;
    typeSensorUsed = _typeSensorUsed;

    dht = new DHT(inputPinUsed, typeSensorUsed);
    dht->begin();
    }

bool TemperatureStub::setUniteUsed(int _UniteUsed){
   if((_UniteUsed>=0) && (_UniteUsed<=1)){
        UniteUsed = _UniteUsed;
        return(true);
        }
    return(false);
    }

//Return -999 if error
float TemperatureStub::getTemperature(){
    float t = dht->readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
        t = lastTemperatureRead;
    }
    lastTemperatureRead = t;
    return(t);
}

//Return -999 if error
float TemperatureStub::getHumidite(){
    float h = dht->readHumidity();
    // Check if any reads failed and exit early (to try again).
    if (isnan(h)) {
        h = lastHumiditeRead;
    }
    lastHumiditeRead = h;
    return(h);
}