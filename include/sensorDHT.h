//Biblioteca para o DHT
#include "DHT.h"
#include "Arduino.h"

#ifndef sensorDHT_H
#define sensorDHT_H

class sensorDHT : DHT
{

    public:
    sensorDHT(uint8_t pin, uint8_t type, uint8_t count = 6) : DHT( pin,  type,  count ){}
    void teste();
    bool readSensor(float *values[3]); //Leitura de todos os valores 
    float heatIndex(bool automaticRead , bool scale, float temperature, float umidity); //Indicie de temperatura
        //Quando automaticRead = true -> Ele irá chamara os próprios métodos do objeto para pegar os valores de temperatura e umidade dentrp da escala escolhida
        //Quando automaticRead = false -> Ele irá utilizar os valores apssados por parâmetro ao método, junto com o tipo de escala.

    private:

};

#endif