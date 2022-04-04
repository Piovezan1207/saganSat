#include "sensorMPU.h"
// Adafruit_MPU6050 mpu;

bool sensorMPU::begin(int sda, int scl, int i2caddr = 0x68){
    Wire.begin(sda,scl);
    if (!Adafruit_MPU6050::begin(i2caddr)) 
    {
      return false;
    }
    return true;
}

bool sensorMPU::setAccRange(int range){
    switch(range)
    {
        case 2: setAccelerometerRange(MPU6050_RANGE_2_G); break;
        case 4: setAccelerometerRange(MPU6050_RANGE_4_G); break;
        case 8: setAccelerometerRange(MPU6050_RANGE_8_G); break;
        case 16: setAccelerometerRange(MPU6050_RANGE_16_G); break;
        default: return false; break;
    }
    return true;
}
int sensorMPU::readAccRange(){
    switch (getAccelerometerRange()) 
    {
        case MPU6050_RANGE_2_G: return 2; break;
        case MPU6050_RANGE_4_G: return 4; break;
        case MPU6050_RANGE_8_G: return 8; break;
        case MPU6050_RANGE_16_G: return 16; break;
        default: return false; break;
        }
}

    
bool sensorMPU::setGirRange(int range){
    switch(range)
    {
        case 250: setGyroRange(MPU6050_RANGE_250_DEG); break;
        case 500: setGyroRange(MPU6050_RANGE_500_DEG); break;
        case 1000: setGyroRange(MPU6050_RANGE_1000_DEG); break;
        case 2000: setGyroRange(MPU6050_RANGE_2000_DEG); break;
        default: return false; break;
    }
    return true;
}

int sensorMPU::readGirRange(){

    switch (getGyroRange()) 
    {
        case MPU6050_RANGE_250_DEG: return 250; break;
        case MPU6050_RANGE_500_DEG: return 500; break;
        case MPU6050_RANGE_1000_DEG: return 1000; break;
        case MPU6050_RANGE_2000_DEG: return 2000; break;
        default: return false; break;
    }

}
bool sensorMPU::setFilterBandwidth(int filterValue){
    //The DLPF is configured by DLPF_CFG. The accelerometer and gyroscope are filtered according to  the value of DLPF_CFG as shown in the table below:
    /*  DLPF_CFG ||    Accelerometer(Fs = 1kHz) ||                Gyroscope
    /            || Bandwidth(Hz) |  Delay(ms)  ||Bandwidth(Hz) | Delay(ms) | Fs(kHz)
        0        ||260            |0            ||256           |0.98       |8
        1        ||184            |2.0          ||188           |1.9        |1
        2        ||94             |3.0          ||98            |2.8        |1
        3        ||44             |4.9          ||42            |4.8        |1
        4        ||21             |8.5          ||20            |8.3        |1
        5        ||10             |13.8         ||10            |13.4       |1
        6        ||5              |19.0         ||5             |18.6       |1
    */

    switch (filterValue)
    {
        case 0: setFilterBandwidth(MPU6050_BAND_260_HZ); break;
        case 1: setFilterBandwidth(MPU6050_BAND_184_HZ); break;
        case 2: setFilterBandwidth(MPU6050_BAND_94_HZ); break;
        case 3: setFilterBandwidth(MPU6050_BAND_44_HZ); break;
        case 4: setFilterBandwidth(MPU6050_BAND_21_HZ); break;
        case 5: setFilterBandwidth(MPU6050_BAND_10_HZ); break;
        case 6: setFilterBandwidth(MPU6050_BAND_5_HZ); break;
        default: return false; break;
    }
    return true;

    
}
int sensorMPU::readFilterBandwidth(){

    switch (getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ: return 0; break;
    case MPU6050_BAND_184_HZ: return 1; break;
    case MPU6050_BAND_94_HZ: return 2; break;
    case MPU6050_BAND_44_HZ: return 3; break;
    case MPU6050_BAND_21_HZ: return 4; break;
    case MPU6050_BAND_10_HZ: return 5; break;
    case MPU6050_BAND_5_HZ: return 6; break;
    default: return 100; break; //Se eu retornar false, será o mesmo que 0, nesse caso, o 100, será um "erro"
    }
}
bool sensorMPU::readSensor(float *returnValues[7]){


    sensors_event_t a, g, temp;
    getEvent(&a, &g, &temp);
    
    float temp = a.acceleration.x;
    memcpy(returnValues + 0, &temp, sizeof(temp));
    float temp = a.acceleration.y;
    memcpy(returnValues + 1, &temp, sizeof(temp));
    float temp = a.acceleration.z;
    memcpy(returnValues + 2, &temp, sizeof(temp));
    
    float temp = g.gyro.x;
    memcpy(returnValues + 3, &temp, sizeof(temp));
    float temp = g.gyro.y;
    memcpy(returnValues + 4, &temp, sizeof(temp));
    float temp = g.gyro.z;
    memcpy(returnValues + 5, &temp, sizeof(temp));

    float temp = temp.temperature;
    memcpy(returnValues + 6 , &temp, sizeof(temp));

}