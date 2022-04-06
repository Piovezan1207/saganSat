#include "sensorDHT.h"
#include "DHT.h"
// sensorDHT::sensorDHT(uint8_t pin, uint8_t type, uint8_t count = 6){

// }

sensorDHT::sensorDHT(uint8_t pin, uint8_t type, uint8_t count ) : DHT( pin,  type,  count ){

}


//Leitura de todos os valores 
bool sensorDHT::readSensor(dhtvalues *values){

  float h = DHT::readHumidity();
  // Read temperature as Celsius (the default)
  float t = DHT::readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = DHT::readTemperature(true);


  values->humidity = h;
  values->temperature_c = t;
  values->temperature_f = f;
    
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {

    return false;
  }

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
