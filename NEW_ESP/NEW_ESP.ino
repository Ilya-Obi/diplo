#include "SerialTransfer.h"
//RX

SerialTransfer myTransfer;

struct STRUCT {
  char z;
  float y;
} testStruct;

float arr1[4] = {};
float arr2[4] = {};

void setup()
{
  Serial.begin(9600);
  myTransfer.begin(Serial);
}


void loop()
{
  if(myTransfer.available())
  {
    // use this variable to keep track of how many
    // bytes we've processed from the receive buffer
    uint16_t recSize = 0;
    myTransfer.rxObj(testStruct, sizeof(testStruct));
    Serial.println("we are printing testStruct:");
    Serial.print("testStruct.z: ");
    Serial.print(testStruct.z);
    Serial.print(' ');
    Serial.print("testStruct.y: ");
    Serial.print(testStruct.y);
    Serial.print(" | ");
    recSize += sizeof(testStruct);
    Serial.println("");
    Serial.println("");


    Serial.println("we are printing arr: ");
    myTransfer.rxObj(arr1, sizeof(arr1), recSize);
    myTransfer.rxObj(arr2, sizeof(arr2), recSize);
    Serial.print("arr1[0]: ");
    Serial.print(arr1[0]);
    Serial.print(' ');
    Serial.print("arr1[1]: ");
    Serial.print(arr1[1]);
    Serial.print(' ');
    Serial.print("arr1[2]: ");
    Serial.println(arr2[0]);
    
    Serial.print("arr1[3]: ");
    Serial.println(arr2[1]);
    Serial.println("");
        Serial.println("");

  }
  else if(myTransfer.status < 0)
  {
    Serial.print("ERROR: ");
    Serial.println(myTransfer.status);
  }
  //delay(5000);  //if we put a very high delay it might be synch errors, infact I get..
                //i.e. error1, error2, ....
}
