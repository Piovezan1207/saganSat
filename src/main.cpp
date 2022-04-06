#include <Arduino.h>

//Bibliotecas WEBserver
#include <WiFi.h>
#include <WebServer.h>
WebServer sv(80);

const char* ssid= "Planta 4.0";                                             //Dados da sua rede Wi-Fi                                                
const char* senha = "";

//Classe para o cartão SD
#include "cartaoSD.h"

operacoesSD sd;

//Classes dos sensores
#include "sensorDHT.h"
#include "sensorMPU.h"

sensorDHT dht(16, DHT11);
dhtvalues dht_values;

sensorMPU mpu;
mpuvalues mpu_values;


void setup(){
    Serial.begin(115200);
    sd.begin();
    dht.begin();
    mpu.begin(15,13, 0x68);
    
    sd.listDir("/", 0);

    mpu.setAccRange(8);
    Serial.printf("\n%i G\n" ,mpu.readAccRange());

    mpu.setGirRange(500);
    Serial.printf("\n%i Deg\n", mpu.readGirRange());
  
    delay(5000);

}
void loop(){
// gps.getValue();
dht.readSensor(&dht_values);
Serial.printf("%.2f %.2f %.2f \n",dht_values.humidity , dht_values.temperature_c, dht_values.temperature_f);

mpu.readSensor(&mpu_values);
Serial.printf("\nAcc: x - %.6f   y - %.6f  z - %.6f\nGiro: x - %.6f   y - %.6f  z - %.6f\nTemp %.6f°\n\n", 
    mpu_values.acc[0],
    mpu_values.acc[1],
    mpu_values.acc[2],
    mpu_values.gir[0],
    mpu_values.gir[1],
    mpu_values.gir[2],
    mpu_values.temp);
delay(1000); 
}
