#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define PA_HUB_ADDRESS 0x70
#define PB_HUB_ADDRESS 0x61 

void setup() {
    Wire.begin(26, 32);
    Serial.begin(9600);
    delay(1000);
    Serial.println("Program run....");
}

void readEnv_iiiSensor(){
    Wire.beginTransmission(PA_HUB_ADDRESS); // PaHub adress
    Wire.write(1 << 1);  // //channel where PbHub is connected to PaHub 
    Wire.endTransmission();
    delay(100); 
    if (!sht31.begin(0x44)) {  // 0x44 address of sht31
         while (1) {
            Serial.println("Couldn't find SHT3X");
            delay(500);
        }
    }
    float temperature = sht31.readTemperature();
    if (!isnan(temperature)) {
        Serial.printf("Temperature: %.2f°C\n", temperature);
    }
}

int readHallSensor() {
        Wire.beginTransmission(PA_HUB_ADDRESS); //PaHub adress
        Wire.write(1 << 0);  //channel where PbHub is connected to PaHub 
        Wire.endTransmission();
        Wire.beginTransmission(PB_HUB_ADDRESS); //PbHub adress
        
        uint8_t error = Wire.endTransmission();
        if (error == 0) {
              int sensorValue = readDigitalPbHub(0x44);
              return sensorValue;
            }
    return 1;
}

int readDigitalPbHub(uint8_t cmd) {
    Wire.beginTransmission(PB_HUB_ADDRESS);
    Wire.write(cmd);
    Wire.endTransmission();
    Wire.requestFrom((uint16_t)PB_HUB_ADDRESS, (uint8_t)1);
    uint8_t regValue = 0;
    if (Wire.available()) {
        regValue = Wire.read();
    }   
    return regValue;
}

void writeOnDigitalPbHub(uint8_t cmd, uint8_t value) {
    Wire.beginTransmission(PB_HUB_ADDRESS);
    Wire.write(cmd);
    Wire.write(value); 
    Wire.endTransmission();
}


void controlRelay(uint8_t state){
    writeOnDigitalPbHub(0x51,state);
}

void loop() {
   if(readHallSensor()){
      controlRelay(HIGH);
   }else{
      controlRelay(LOW);
   }
   delay(100); 
   readEnv_iiiSensor();
   delay(100); 
}
