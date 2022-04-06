#include "Arduino.h"

//Bibliotecas para o MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#ifndef sensorMPU_H
#define sensorMPU_H

typedef struct {
  float acc[3]; 
  float gir[3]; 
  float temp; 

} mpuvalues;

class sensorMPU : Adafruit_MPU6050 {

    public:
    bool begin(int sda, int scl, int i2caddr = 0x68);
    bool setAccRange(int range);
    int readAccRange();
    bool setGirRange(int range);
    int readGirRange();
    bool setFilterBandwidth(int filterValue);
    int readFilterBandwidth();
    bool readSensor(mpuvalues *values);

    private:

};

#endif