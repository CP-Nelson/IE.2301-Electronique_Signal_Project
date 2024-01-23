const int sampleWindow = 50;  // Sample window width in mS (50 mS = 20Hz)
int const AMP_PIN = A1;       // Preamp output pin connected to A0
unsigned int sample;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 4096;

  // collect data for 50 mS and then plot data
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(AMP_PIN);
    if (sample < 4096)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
//  Serial.println("peakTopeak=");
float dbvalue;
 dbvalue = 20*log(analogRead(AMP_PIN)/300);
  Serial.println(analogRead(AMP_PIN));
//  Serial.println();
//  Serial.println("Volts=");
//  double volts = (peakToPeak * 5) / 1000;  // convert to volts
//   normal silence is lower than 150, effective sound is between 500 to 3000
//if(peakToPeak>1200)
//  Serial.println(peakToPeak);
  delay(100);
}
