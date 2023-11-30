byte PWM_IN = PF_1;                  // PWM input to be read at Arduino UNO's PWM pin 3
 
int value;              
 
void setup() 
{
  pinMode(PWM_IN, INPUT);                     // initialising PWM_IN as an input pin
  Serial.begin(9600);                       
}
 
void loop()   
{
  value = pulseIn(PWM_IN, HIGH);               // using pulseIn function of arduino (this function starts counting until a pulse remains high )
  Serial.println(value);                  //printing Angle :  on serial monitor
}
