#include "GPS.h"

GPS::GPS( int rx, int tx) : SoftwareSerial(rx, tx){
}

void GPS::teste(){
  Serial.println("a");
}

bool GPS::begin(int serialVel){
    SoftwareSerial::begin(serialVel);
}

String GPS::getValue(){
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (SoftwareSerial::available())
    {
      char c = SoftwareSerial::read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (TinyGPS::encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    TinyGPS::f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(TinyGPS::satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : TinyGPS::satellites());
    Serial.print(" PREC=");
    Serial.print(TinyGPS::hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : TinyGPS::hdop());
  }
  
  TinyGPS::stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}