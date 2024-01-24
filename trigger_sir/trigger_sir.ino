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
