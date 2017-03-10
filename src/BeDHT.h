/*
  BeDHT.h - Sample Code of BeDHT Library .
  Created by benjenq, March 3, 2017.

  Depends on the following Arduino libraries:
  - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
*/

#ifndef BeDHT_n
#define BeDHT_n

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

class BeDHT {
  public:
    BeDHT();
    BeDHT(char *cname, int pin,uint8_t type);
    void begin(char *cname, int pin,uint8_t type);
    void readValue();
    sensor_t temperatureSensorInfo();
    sensor_t humiditySensorInfo();
    
    typedef void(*callbackread)(BeDHT bedht);
    void setBeDHTCallback(callbackread rcb);
    //protected:
    char *name;
    float temperatureCelsius;
    float temperatureFahrenheit;
    float humidity;
    float hiCelsius;
    float hiFahrenheit;

    
    bool readsuccess;

  private:
    int _pin;
    uint8_t _type;
    callbackread _rcb;

};
#endif
