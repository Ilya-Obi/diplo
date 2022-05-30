#include "SerialTransfer.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define SEALEVELPRESSURE_HPA (1013.25)
//TX

SerialTransfer myTransfer;


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

//Adafruit_BME680 bme; 
Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

float temperature;
float humidity;
float pressure;
float gasResistance;

struct STRUCT {
  char z;
  float y;
} testStruct;

float arr1[4] = {0, 1, 2, 3};
float arr2[4] = {0, 1, 2, 3};

void getBME680Readings(){
  // Tell BME680 to begin measurement.
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }
  
}


void setup()
{
  //Serial.begin(115200);
  Serial.begin(9600);
  myTransfer.begin(Serial);
  Serial.println(F("BME680 async test"));
  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); 
}


void loop()
{

  Serial.print(F("Temperature = "));
Serial.print(bme.temperature);
Serial.println(F(" *C"));

Serial.print(F("Pressure = "));
Serial.print(bme.pressure / 100.0);
Serial.println(F(" hPa"));

Serial.print(F("Humidity = "));
Serial.print(bme.humidity);
Serial.println(F(" %"));

Serial.print(F("Gas = "));
Serial.print(bme.gas_resistance / 1000.0);
Serial.println(F(" KOhms"));

Serial.print(F("Approx. Altitude = "));
Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
Serial.println(F(" m"));
  
  temperature = bme.temperature;
  pressure = bme.pressure / 100.0;
  humidity = bme.humidity;
  gasResistance = bme.gas_resistance / 1000.0;
  testStruct.z = '|';
  arr1[0] = bme.temperature;
  arr1[1] = bme.pressure/100.0;
  arr2[0] = bme.gas_resistance / 1000.0;
  arr2[1] = bme.gas_resistance/1000.0;
  // use this variable to keep track of how many
  // bytes we're stuffing in the transmit buffer
  uint16_t sendSize = 0;

  ///////////////////////////////////////// Stuff buffer with individual bytes

  ///////////////////////////////////////// Stuff buffer with struct
  myTransfer.txObj(testStruct, sizeof(testStruct));
  sendSize += sizeof(testStruct);

  ///////////////////////////////////////// Stuff buffer with array
  myTransfer.txObj(arr1, sizeof(arr1), sendSize);
  sendSize += sizeof(arr1);
  myTransfer.txObj(arr1, sizeof(arr1), sendSize);  
  sendSize += sizeof(arr1);
  

  

  ///////////////////////////////////////// Send buffer
  myTransfer.sendData(sendSize);
  myTransfer.txObj(arr2, sizeof(arr2), sendSize);  
  sendSize += sizeof(arr2);
  myTransfer.sendData(sendSize);
  delay(1000);
}
