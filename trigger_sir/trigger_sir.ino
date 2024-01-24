//-----------------------------------------------------------------------------
//
// Power Measurement (Signal from microphone electret).
//
//  Read the comments and understand the program.
//  Replace the “????” with a suitable value before running the program.
// Step-1 : Goto ##TAG##1 and determine SAMPLE_FREQ and SIZE_BUFF
// Step-2 : Goto ##TAG##2 read and understand the sampling function
// Step-3 : Goto ##TAG##3 Translate your Matlab program to calculate the mean power
// Step-4 : Goto ##TAG##4 Set the microphone pin and determine the LOW, MAX and AVR level
// Step-5 : Goto ##TAG##5 Complete the main program loop()
//-----------------------------------------------------------------------------

//---co2
#ifndef __MICS_VZ_89TE_H__
#define __MICS_VZ_89TE_H__

#include "Arduino.h"

#define MICS_VZ_89TE_ADDR                0x70 //0x70 default I2C address
//registers
#define MICS_VZ_89TE_ADDR_CMD_GETSTATUS  0x0C  // This command is used to read the VZ89 status coded with 6 bytes:
#define MICS_VZ_89TE_DATE_CODE           0x0D

class MICS_VZ_89TE {
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

    float year;
    float month;
    float day;
    float rev;
    float crc;

    void begin(void);
    void readSensor(void);
    void getVersion(void);

private:
    uint8_t _i2caddr;
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
    voc = (data[0] - 13) * (1000.0 / 229);       // ppb: 0 .. 1000
//    co2 = data[1]; // ppm: 400 .. 2000
//    voc = data[0]; // ppb: 0 .. 1000
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

void MICS_VZ_89TE::begin(void) {
    Wire.begin();
}

void MICS_VZ_89TE::readData(byte reg, uint8_t data[]) {
    uint8_t i = 0;
    Wire.beginTransmission((uint8_t)_i2caddr);
    Wire.write((uint8_t)reg); // This sends the command to get data
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.endTransmission();

    Wire.beginTransmission(0xE1);
    Wire.endTransmission();

    Wire.requestFrom((uint8_t)_i2caddr, (byte)7);
    for (i = 0; i < 7; i++) {
        data[i] = Wire.read();
    }
}

MICS_VZ_89TE CO2SENSOR;
//---

#define MICROPHONE_PIN  A4
#define temperSensorPin A6
#define Red_LED PF_1
#define Blue_LED PF_2
#define Green_LED PF_3

#define   LOW_LEVEL   3000
#define   MAX_LEVEL   3500
#define   AVR_LEVEL   0.2*MAX_LEVEL

#define   SAMPLE_FREQ 4000 
#define   SIZE_BUFF 1000   
#define   SAMPLE_PERIOD (1000/SAMPLE_FREQ)*1000000


//  Signal samples Buffer
double Buffer_Sample[SIZE_BUFF];
// Buffer de la Puissance instantannée du signal en flottant
float Power_Inst[SIZE_BUFF];
double Read_Samples(void);
double powerCalcul(int arraySize, short amplitude[1000]);

////------------------------------Filter part start----------------------------------
//#include "main.h"
//#include "filter2.h"
//#include "filter2_terminate.h"
//#include "rt_nonfinite.h"
//static void argInit_1000x1_real_T(double result[1000]);
//static double argInit_real_T(void);
//
//static void argInit_1000x1_real_T(double result[1000])
//{
//  int idx0;
//  /* Loop over the array to initialize each element. */
//  for (idx0 = 0; idx0 < 1000; idx0++) {
//    /* Set the value of the array element.
//Change this value to the value that the application requires. */
//    result[idx0] = Buffer_Sample[idx0];
//  }
//}
//
//static double argInit_real_T(void)
//{
//  return 0.0;
//}
//
//double main_filter2(void)
//{
//  double dv[1000];
//  double Energy;
//  argInit_1000x1_real_T(dv);
//  Energy = filter2(SAMPLE_FREQ, dv);
//  return Energy;
//}
//
////------------------------------Filter part end----------------------------------



void setup()
//-----------------------------------------------------
// Initialization function
//-----------------------------------------------------
{
  Serial.begin(9600);
Serial1.begin(9600);
Serial1.write("AT+NAMEG2");
  pinMode(MICROPHONE_PIN, INPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Blue_LED, OUTPUT);
    Wire.setModule(0);
    Wire.begin();
}


//---------*********Main Function*********---------
void loop()
{
  Serial1.println("-----Data presentation (per second)-----");
//Temperature part
  int temper = analogRead(temperSensorPin);
  float voltage = temper * (1.1/ 4095.0);
  float temperatureC = voltage/0.01;
  Serial1.print("Temperature: ");
  Serial1.print(temperatureC);
  Serial1.print("°C ");
  Serial1.println();
//-------------
//---CO2 part
    CO2SENSOR.readSensor();
    float co2 = CO2SENSOR.getCO2();
    float voc = CO2SENSOR.getVOC();

    Serial1.print("CO2: ");
    Serial1.print(co2);
    Serial1.print("ppm");
  Serial1.println();
    Serial1.print("VOC: ");
    Serial1.print(voc);
    Serial1.print("ppb");
  Serial1.println();
//-------------
  // Déclaration de variables
  double SoundPower;   // puissance du Son
//  double FilteredEnergy;
  Serial.println(" ");
  SoundPower = Read_Samples();
//  FilteredEnergy = main_filter2();
//  Serial.println(FilteredEnergy);
//  filter2_terminate();

  Serial.print(" Power = ");
  Serial.println(SoundPower);
  Serial1.print("Sound Power: ");
  Serial1.print(SoundPower);
  Serial1.println();
  if (SoundPower < LOW_LEVEL) {
  digitalWrite(Blue_LED, LOW);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, HIGH); 
  Serial.println("Sound power below threshold. LED turned off.");
  Serial1.println("No meaningful sounds.");
  }
  else if (SoundPower > LOW_LEVEL) { 
  digitalWrite(Blue_LED, HIGH);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, LOW); 
  Serial.println("The power of your input signal is too high.");
  Serial1.println("Sound detected.");
  }
  else {
    Serial.println("High sound power detected. LED turned on.");
  }
  delay(500);
}

//----------------------------------------------------------Sample----------------------------------------------------------
double Read_Samples(void)
{
  short num_sample;
  double  val_sample;
  unsigned long curtime, nextime;
  // See help of 'micros()' function in Energia
  // compute next sampling time (nextime)
  nextime = micros() + SAMPLE_PERIOD;
  num_sample = 0;
  while (num_sample < SIZE_BUFF) {
    // wait time of next sample (nextime)
    do {
      curtime = micros();
    } while (curtime < nextime);
    // read sample
    val_sample = analogRead(MICROPHONE_PIN);
    Buffer_Sample[num_sample] = val_sample;
    num_sample++;
    // update next sample time
    nextime += SAMPLE_PERIOD;
  }
//  Serial.println(curtime/1000000);
  double power;
  power = powerCalcul(SIZE_BUFF,Buffer_Sample);
  return power;
}

double powerCalcul(int arraySize, double amplitude[SIZE_BUFF]){
  double energySum,power;
  for(int i = 0;i<arraySize;i++){
    amplitude[i] -= 3200;
    amplitude[i] /=10;
    energySum+=amplitude[i]*amplitude[i];}
  double timeLength = arraySize/SAMPLE_FREQ;
  power = energySum*SAMPLE_FREQ/SIZE_BUFF/1000;
  return power;
}
