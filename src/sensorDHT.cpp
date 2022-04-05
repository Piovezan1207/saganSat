#include "sensorDHT.h"

// sensorDHT::sensorDHT(uint8_t pin, uint8_t type, uint8_t count = 6){

// }

sensorDHT::sensorDHT(uint8_t pin, uint8_t type, uint8_t count ) : DHT( pin,  type,  count ){

}

void sensorDHT::teste(){}

//Leitura de todos os valores 
bool sensorDHT::readSensor(float *values[3]){

  float ah = DHT::readHumidity();
  // Read temperature as Celsius (the default)
  float at = DHT::readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float af = DHT::readTemperature(true);

     ah = 1;
      at = 11;
      af = 11;

    float *h = &ah;
    float *t = &at;
    float *f = &af;

    Serial.println(ah);
    // Serial.printf("%f %f %f \n", &h,&t,&f);
    
  // Check if any reads failed and exit early (to try again).
  if (isnan(ah) || isnan(at) || isnan(af)) {
     
    
    memcpy(values + 0, &h, sizeof(h));
    memcpy(values + 1, &t, sizeof(t));
    memcpy(values + 2, &f, sizeof(f));

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
