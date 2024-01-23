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

// ##TAG##4 deb
#define    MICROPHONE_PIN  A1
#define Red_LED PF_1
#define Blue_LED PF_2
#define Green_LED PF_3

// You must determine the power measured with no sound
// this is the low level value in the below line
#define   LOW_LEVEL   100

// You must determine the power measured with the maximum Sound
#define   MAX_LEVEL   1500

// You have to choose the average acceptable value of power
// It can be nn% of the MAX_LEVEL
#define   AVR_LEVEL   0.2*MAX_LEVEL
// ##TAG##4 end

// Function define
double Read_Samples(void);
//float Get_Soud_Power(void);
//double meanCalcul(int arraySize, short amplitude[1000]);
double powerCalcul(int arraySize, short amplitude[1000]);

void setup()
//-----------------------------------------------------
// Initialization function
//-----------------------------------------------------
{
  // Serial port baud rate = 9600 bauds
  Serial.begin(9600);
  // Initialize the sensor input as an analog input
  pinMode(MICROPHONE_PIN, INPUT);
    pinMode(Red_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Blue_LED, OUTPUT);
}



// ##TAG##5 deb
void loop()
//-----------------------------------------------------
// Main Fonction
//-----------------------------------------------------
{
  // Déclaration de variables
  float SoundPower;   // puissance du Son

  Serial.println(" ");
//  Serial.println("--- Sound Power Measurement ---");

  // call the function.

  SoundPower = Read_Samples();

  // Display the result
  Serial.print(" Power = ");
  Serial.println(SoundPower);
  if (SoundPower < LOW_LEVEL) {
  digitalWrite(Blue_LED, LOW);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, HIGH); 
    Serial.println("Sound power below threshold. LED turned off.");
    // Power is too low = no sound
    // display an explicit message and turn on the white LED
  }
  else if (SoundPower > LOW_LEVEL) { 
  digitalWrite(Blue_LED, HIGH);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, LOW); 
    Serial.println("The power of your input signal is too high.");
    // Power is too high = sound is painful
    // display an explicit message and turn on the red LED
  }
  else {
    Serial.println("High sound power detected. LED turned on.");
    // acceptable power
    // display an explicit message and turn on the green LED
  }

  // wait 0.5 second
  delay(500);
}
// ##TAG##5 end


// ##TAG##1 deb
// Define the sampling parameters
//---------------------------------------------------------------
//  Choose the sampling frequency (in Hz)
#define   SAMPLE_FREQ 4000    /* frequency between 4 and 8 KHz    */
//  Choose the size of samples buffer
#define   SIZE_BUFF 1000    /* value between 1000 and 4000  */
// ##TAG##1 end

//  Sampling period in micro-secondes
#define   SAMPLE_PERIOD (1000/SAMPLE_FREQ)*1000000
//  Signal samples Buffer
short Buffer_Sample[SIZE_BUFF];

// Buffer de la Puissance instantannée du signal en flottant
float Power_Inst[SIZE_BUFF];


// ##TAG##2 deb
double Read_Samples(void)
//------------------------------------------------------------------------------
// No need to modify this function. Read and understand
//------------------------------------------------------------------------------
{
  short num_sample, val_sample;
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
//power = 0.8;
  return power;
}
// ##TAG##2 end

//// ##TAG##3 deb
//float Get_Sound_Power(void)
////------------------------------------------------------------------------------
////  Read signal and compute mean power
////------------------------------------------------------------------------------
//{
//  double power;
//  power = powerCalcul(1000,Buffer_Sample);
////power = 0.8;
//  return power;
//}
//// ##TAG##3 end


//double meanCalcul(int arraySize, short amplitude[1000]){
//  double energySum,energyMean;
//  for(int i = 0;i<arraySize;i++)
//    energySum+=amplitude[i];
//  double timeLength = arraySize/4000;
//  energyMean = energySum/timeLength;
//  return energyMean;
//}

double powerCalcul(int arraySize, short amplitude[SIZE_BUFF]){
  double energySum,power;
  for(int i = 0;i<arraySize;i++){
    amplitude[i] -= 3200;
    amplitude[i] /=10;
    energySum+=amplitude[i]*amplitude[i];}
  double timeLength = arraySize/4000;
  power = energySum*4/1000;
  return power;
}
