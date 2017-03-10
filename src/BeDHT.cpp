/*
  BeDHT.cpp - Sample Code of BeDHT Library .
  Created by benjenq, March 3, 2017.

  Depends on the following Arduino libraries:
  - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
*/

#include "BeDHT.h"

BeDHT::BeDHT() {
  readsuccess = false;
}

BeDHT::BeDHT(char *cname, int pin, uint8_t type) {
  pinMode(pin, INPUT);
  _pin = pin;
  _type = type;
  name = cname;
  readsuccess = false;

}

void BeDHT::begin(char *cname, int pin, uint8_t type) {
  pinMode(pin, INPUT);
  _pin = pin;
  _type = type;
  name = cname;
  readsuccess = false;

}

sensor_t BeDHT::temperatureSensorInfo() {
  DHT_Unified dht(_pin, _type);

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  return sensor;
}

sensor_t BeDHT::humiditySensorInfo() {
  DHT_Unified dht(_pin, _type);
  sensor_t sensor;
  dht.humidity().getSensor(&sensor);
  return sensor;
}

void BeDHT::readValue() {
  DHT dht(_pin, _type);
  dht.begin();
  humidity = dht.readHumidity();
  temperatureCelsius = dht.readTemperature();
  temperatureFahrenheit = dht.readTemperature(true);
  
  // Compute heat index in Fahrenheit (the default)
  hiCelsius = dht.computeHeatIndex(temperatureCelsius, humidity, false);
  // Compute heat index in Celsius (isFahreheit = false)
  hiFahrenheit = dht.computeHeatIndex(temperatureFahrenheit, humidity);

  if (isnan(temperatureCelsius) || isnan(temperatureFahrenheit) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    readsuccess = false;
    _rcb(*this); //Read failed
  }
  else
  {
    //Serial.println("read from DHT sensor!");
    readsuccess = true;
    _rcb(*this); //Read success
  }
}

void BeDHT::setBeDHTCallback(callbackread rcb) {
  _rcb = rcb;
}
