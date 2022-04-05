#include "sensorDHT.h"

// sensorDHT::sensorDHT(uint8_t pin, uint8_t type, uint8_t count = 6){

// }

void sensorDHT::teste(){}

//Leitura de todos os valores 
bool sensorDHT::readSensor(float *values[3]){

  float h = readHumidity();
  // Read temperature as Celsius (the default)
  float t = readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    return false;
  }

    memcpy(values + 0, &h, sizeof(h));
    memcpy(values + 1, &t, sizeof(t));
    memcpy(values + 2, &f, sizeof(f));

    return true;
} 


//Indicie de temperatura
float sensorDHT::heatIndex(bool automaticRead , bool scale, float temperature, float umidity){

    if (automaticRead){
        if (scale)
            return computeHeatIndex(readTemperature(), readHumidity(), false); //Indicies em C
        else
            return computeHeatIndex(readTemperature(true), readHumidity(), true);//Indicie em F
    }
    else{
         if (scale)
            return computeHeatIndex(temperature, umidity, false); //Indicies em C
        else
            return computeHeatIndex(temperature, umidity, true);//Indicie em F
    }
}
