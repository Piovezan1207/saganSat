#include "Arduino.h"
#include "TinyGPS.h"
#include "SoftwareSerial.h"

#ifndef GPS_H
#define GPS_H

//Biblioteca para o DHT

class GPS :TinyGPS , SoftwareSerial
{

    public:
        void teste();
        GPS(int rx, int tx) ;
        bool begin(int serialVel);
        String getValue();
    private:

};

#endif