#include <Arduino.h>

// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include "cartaoSD.h"

operacoesSD cartaosd();




#include "FS.h" 
#include "SD_MMC.h" 

//Bibliotecas WEBserver
#include <WiFi.h>
#include <WebServer.h>

//Biblioteca de arquivos
#include <SPIFFS.h>

//Bibliotecas para o MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <SoftwareSerial.h>

#include "DHT.h"
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void dhtRead();
// Best for Teensy LC & 3.2
//SoftwareSerial mySerial(0, 1); // RX,TX
SoftwareSerial gpsSerial(14,2);

void leituraGPS();

bool useMPU = true;
//Instancia do webserver
WebServer sv(80);

//Instancia do sensor
Adafruit_MPU6050 mpu;

const char* ssid= "Planta 4.0";                                             //Dados da sua rede Wi-Fi                                                
const char* senha = "";

String leituraMPU_html();

void nao_encontrado() {                                                           //Sub-rotina para caso seja retornado um erro
  sv.send(404, "text/plain", "Não encontrado");                                   //Retorna a mensagem de erro em caso de um retorno 404
}



bool loadFromSPIFFS(String path) {
  String dataType = "text/html";
 
  Serial.print("Requested page -> ");
  Serial.println(path);
  if (SPIFFS.exists(path)){
      File dataFile = SPIFFS.open(path, "r");
      if (!dataFile) {
          nao_encontrado();
          return false;
      }
 
      if (sv.streamFile(dataFile, dataType) != dataFile.size()) {
        Serial.println("Sent less data than expected!");
      }else{
          Serial.println("Page served!");
      }
 
      dataFile.close();
  }else{
      nao_encontrado();
      return false;
  }
  return true;
}

void conectado() {                                                                //Sub-rotina para caso o servidor fique online
  // sv.send(200, "text/html", "<html>Salve</html>");                              //Envia ao servidor, em formato HTML, o nosso script, com os parâmetros de pressão e temperatura
  loadFromSPIFFS("/index.html");
}

void lerSensor() {                                                                //Sub-rotina para caso o servidor fique online
  sv.send(200, "text/html", leituraMPU_html());                              //Envia ao servidor, em formato HTML, o nosso script, com os parâmetros de pressão e temperatura
}

void inicializacao_wifi()
{
  Serial.print("Se conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);                                                        //Se conecta ao Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {                                         //Verifica se a conexão foi bem-sucedida
    delay(4000);
    Serial.print(".");
  }
  Serial.println("\nConectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());  

}

void inicializacao_webserver()
{
  
  sv.on("/", conectado);
  sv.on("/values", lerSensor);
  sv.onNotFound(nao_encontrado);
  sv.begin();                                                                     //Inicia o servidor
  Serial.println("Servidor Online");
}

void inicializacao_SPIFFS()
{
    Serial.print(F("Inizializing FS..."));
  if (SPIFFS.begin()){
    Serial.println(F("done."));
  }else{
    Serial.println(F("fail."));
  }
}

void setup(void) {
  gpsSerial.begin(9600);
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

    dht.begin();

    while(1)  dhtRead();

    leituraGPS();

  inicializacao_wifi();
  inicializacao_webserver();
  inicializacao_SPIFFS();

  if(useMPU )
  {
    Serial.println("Adafruit MPU6050 test!");

    Wire.begin(15,13);

    // Try to initialize!
    // uint8_t i2c_add = 12;
    if (!mpu.begin(0x68 )) {
      Serial.println("Failed to find MPU6050 chip");
      while (1) {
        delay(10);
      }
    }
    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
    }
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
    }

    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
    }

    Serial.println("");
    delay(100);
  }
}

void loop() {

  sv.handleClient();              

  
}

bool flag = false;
String values = "";

void dhtRead()
{
      // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void leituraGPS()
{

    while(!gpsSerial.available() > 0);
    while(gpsSerial.available() > 0)
    {
        char x;
        x = gpsSerial.read();
        values += x;
        delay(1);
        flag = true;
    }
    if(flag)
    {
        flag = false;
        Serial.println( values);
        values = "a";
        delay(1000);
    }
}

String leituraMPU_html()
  {
    if(useMPU)
  {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float Ax, Ay, Az, Gx, Gy, Gz, T;

    Ax = a.acceleration.x;
    Ay = a.acceleration.y;
    Az = a.acceleration.z;

    Gx = g.gyro.x;
    Gy = g.gyro.y;
    Gz = g.gyro.z;

    T = temp.temperature;

    String HTML_table_values = "";

    float valores [7] = {Ax,Ay,Az,Gx,Gy,Gz,T};
    String Sensores [7] = {"Acelerometro","Acelerometro","Acelerometro","Giroscopio","Giroscopio","Giroscopio","Temperatura"}; 
    String letras [7] = {"X","Y","Z","X","Y","Z","TEMP"}; 
    
    HTML_table_values += "<table><tr><th>Sensor</th><th>Eixo</th><th>Valor</th></tr><tr><th>-</th><th>-</th><th>-</th></tr>";


    for (int i = 0; i < 7; i++)
    {
      HTML_table_values += "<tr>";
        HTML_table_values += "<th>";
        HTML_table_values += Sensores[i];
        HTML_table_values += "</th>";

        HTML_table_values += "<th>";
        HTML_table_values += letras[i];
        HTML_table_values += "</th>";

        HTML_table_values += "<th>";
        HTML_table_values +=  String (valores[i]);
        HTML_table_values += "</th>";
      HTML_table_values += "</tr>";
    }
      HTML_table_values += "</table>";
    
    
    return (HTML_table_values);


    // /* Print out the values */
    // Serial.print("Acceleration X: ");
    // Serial.print(a.acceleration.x);
    // Serial.print(", Y: ");
    // Serial.print(a.acceleration.y);
    // Serial.print(", Z: ");
    // Serial.print(a.acceleration.z);
    // Serial.println(" m/s^2");

    // Serial.print("Rotation X: ");
    // Serial.print(g.gyro.x);
    // Serial.print(", Y: ");
    // Serial.print(g.gyro.y);
    // Serial.print(", Z: ");
    // Serial.print(g.gyro.z);
    // Serial.println(" rad/s");

    // Serial.print("Temperature: ");
    // Serial.print(temp.temperature);
    // Serial.println(" degC");

    // Serial.println("");
    // delay(500);
  }
  else{
    return "O sensor esta de";
  }
  }