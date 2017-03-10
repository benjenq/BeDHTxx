/*
  BeDHTxx_Sample.ino - Sample Code of BeDHTxx Library. Support DHT11,DHT21,DHT22 sensor/module.
  Created by benjenq, March 2, 2017.

  BeDHT([Name],[#pin],DHTTYPE) , can assign name for each DHTxx and callback with name.

  Depends on the following Arduino libraries:
  - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

  Sample:
  BeDHT beSensor("MyRoom",2,DHTTYPE); //-->Use name MyRoom and DHT11 was plun on pin 2 
  (Arduino Hardware: pin2, Esp8266: GPIO 2...etc. Change by your hardware)

  //Set call back method:
  void readSensorCallBack(BeDHT [bedhtname]) {...}

  setup():
  beSensor.setBeDHTCallback(readSensorCallBack);

  loop():
  beSensor.readValue(); // read value method then call back method.
*/

#include "BeDHT.h"

#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

BeDHT beSensor("MyRoom", 2, DHTTYPE);

void readSensorCallBack(BeDHT bedht) {
  if (bedht.readsuccess) {
    Serial.println("===============================================");
    Serial.print("Name: ");
    Serial.print(bedht.name);
    Serial.print("\t Humidity: ");
    Serial.print(bedht.humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(bedht.temperatureCelsius);
    Serial.print(" *C ");
    Serial.print(bedht.temperatureFahrenheit);
    Serial.print(" *F | ");
    Serial.print(bedht.hiCelsius);
    Serial.print(" *C ");
    Serial.print(bedht.hiFahrenheit);
    Serial.println(" *F");
    Serial.println("");
  }
  else
  {
    Serial.println("===ReadSensor Failed!!=====");
  }

}

void setup() {
  Serial.begin(115200);
  beSensor.setBeDHTCallback(readSensorCallBack);
  printSensorInfo();

}

void loop() {
  // start working...
  beSensor.readValue();

  delay(2000);
}

// Optinal Method

void printSensorInfo() {
  // Print temperature sensor details.
  sensor_t tempSensor = beSensor.temperatureSensorInfo();
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(tempSensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(tempSensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(tempSensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(tempSensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(tempSensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(tempSensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");

  // Print humidity sensor details.
  sensor_t humiSensor = beSensor.humiditySensorInfo();
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(humiSensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(humiSensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(humiSensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(humiSensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(humiSensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(humiSensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
}
