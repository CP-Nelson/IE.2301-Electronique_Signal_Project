
/***************************************************************************
 
 Hervé Grabas
  
 This is a library for the MICS-VZ-89TE Indoor Air Quality Sensor from SGX Sensortech Limited.
 
 
 ***************************************************************************/

#ifndef __MICS_VZ_89TE_H__

#define __MICS_VZ_89TE_H__

#include "Arduino.h"
#include "Wire.h"


#define MICS_VZ_89TE_ADDR      0x70 //0x70 default I2C address
//registers
#define MICS_VZ_89TE_ADDR_CMD_GETSTATUS  0x0C  // This command is used to read the VZ89 status coded with 6 bytes:
#define MICS_VZ_89TE_DATE_CODE 0x0D


/*=========================================================================

Main Class for the MICS_VZ_89TE library

=========================================================================*/


class MICS_VZ_89TE

{
    
public:
    MICS_VZ_89TE(void);
    // To get the data
    float getCO2(void);
    float getVOC(void);
    float getYear(void);
    float getMonth(void);
    float getDay(void);
    float getRev(void);
    float getCrc(void);
    float getStatus(void);
    
    float co2;
    float voc;
    float status;
    
    float year ;
    float month;
    float day;
    float rev;
    float crc;
    
    void begin(void);
    void readSensor(void);
    void getVersion(void);
    
    
private:
    
    uint8_t   _i2caddr;
    void readData(byte reg, uint8_t data[]);

};

#endif


#include <math.h>
#include <Wire.h>

MICS_VZ_89TE::MICS_VZ_89TE(void) {
    _i2caddr = MICS_VZ_89TE_ADDR;
    co2 = 0.0;
    voc = 0.0;
}

float MICS_VZ_89TE::getCO2(void) {
    return co2;
}

float MICS_VZ_89TE::getVOC(void) {
    return voc;
}

float MICS_VZ_89TE::getYear(void) {
    return year;
}

float MICS_VZ_89TE::getMonth(void) {
    return month;
}

float MICS_VZ_89TE::getDay(void) {
    return day;
}

float MICS_VZ_89TE::getRev(void) {
    return rev;
}

float MICS_VZ_89TE::getCrc(void) {
    return crc;
}

float MICS_VZ_89TE::getStatus(void) {
    return status;
}

void MICS_VZ_89TE::readSensor(void) {
    static uint8_t data[7];
    readData(MICS_VZ_89TE_ADDR_CMD_GETSTATUS, data);
    
    status = data[5];
    
    co2 = (data[1] - 13) * (1600.0 / 229) + 400; // ppm: 400 .. 2000
    voc = (data[0] - 13) * (1000.0/229); // ppb: 0 .. 1000

}

void MICS_VZ_89TE::getVersion(void) {
    static uint8_t data[7];
    readData(MICS_VZ_89TE_DATE_CODE, data);
    
    year = data[0];
    month = data[1];
    day = data[2];
    rev = data[3];
    crc = data[6];
}


void MICS_VZ_89TE::begin() {
    Wire.begin();
}

/*
 After Power-on self-test (2 seconds) , the device will provide either a single “Failed Diagnostic
 Level” in case of sensor failure of the sensor or PWM multiplexed output indicating
 “CO_ equivalent_ Level” and “VOC _isobutylene_equivalent Level” referred to the isobutylene
 sensitivity unit.
 
 Out of this initial period, the device will have the I2C data CO2 equivalent [ppm] and tVOC equivalent
 referred to the isobutylene sensitivity unit [ppb].
 
 D1 : Data_byte_1: VOC_short [13…242]
 D2 : Data_byte_2: CO2_equ: [13…242] -> CO2_equ [ppm] = (D2 -13) * (1600/229) + 400
 D3 : Data_byte_3: Raw sensor first byte (MSB)
 D4 : Data_byte_4: Raw sensor second byte
 D5 : Data_byte_5: Raw sensor third byte (MSB) -> Resistor value [W] = 10*(D5+ (256*D4) + (65536*D3))
 D6 : Status
 D7 : CRC
 
 return CO2 equivalent [ppm] and tVOC equivalent referred to the isobutylene sensitivity unit [ppb].
 *
 */
void MICS_VZ_89TE::readData(byte reg, uint8_t data[]) {
    uint8_t i =0;
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg); //This send the command to get data
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.endTransmission();
    
    Wire.beginTransmission(0xE1);
    Wire.endTransmission();
    
    Wire.requestFrom((uint8_t)_i2caddr, (byte)7);
    for (i=0; i<7; i++) {
    data[i] = Wire.read();
    }

}


MICS_VZ_89TE CO2SENSOR;

void setup() {
  // Open serial communications and wait for port to open:
 // delay(1000);
 Wire.begin(10, 9);
 Wire.beginTransmission(0x70);
 Wire.endTransmission();
  Serial.begin(9600);
  //while (!Serial) {
   // ; // wait for serial port to connect. Needed for native USB port only
 // }
  Serial.print("CO2: ");
  CO2SENSOR.begin();
 //delay(1000);
  Serial.println("MICS-VZ-89TE Example");

}

void loop() { // run over and over
//delay(1000);

  CO2SENSOR.readSensor();
//delay(1000);
  float co2 = CO2SENSOR.getCO2();
  //delay(1000);
  float voc = CO2SENSOR.getVOC();

  Serial.print("CO2: ");
  Serial.println(co2);
//delay(1000);
  Serial.print("VOC: ");
  Serial.println(voc);

  delay(500);
}
