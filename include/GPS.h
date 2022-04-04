#ifndef GPS_H
#define GPS_H

#include "Arduino.h"
#include "TinyGPS.h"
#include "SoftwareSerial.h"

//Biblioteca para o DHT




class GPS :TinyGPS , SoftwareSerial
{

    public:
        GPS(int serialVel , int rx, int tx) : SoftwareSerial(rx, tx){}

    private:

};

#endif