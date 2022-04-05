#include <Arduino.h>

#include "GPS.h"
#include "cartaoSD.h"
#include "sensorDHT.h"
#include "sensorMPU.h"

operacoesSD sd;

sensorDHT dht(16, DHT11);

// GPS gps(14,2);

void setup(){
    Serial.begin(115200);
    sd.begin();
    sd.listDir("/", 0);
    // gps.begin(9600);
  
}
void loop(){
// gps.getValue();
float *values[3];
dht.readSensor(&values[3]);



for (byte i = 0; i <3; i++) {
    Serial.printf("%f", values[i]);
    Serial.print(" ");
}
Serial.println();
delay(1000);
}
