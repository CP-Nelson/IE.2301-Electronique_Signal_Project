#define temperSensorPin A6

void setup() {
  Serial.begin(9600);
}

void loop() {
  int temper = analogRead(temperSensorPin);
  float voltage = temper * (1.1/ 4095.0);
  float temperatureC = voltage/0.01;
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print("°C  ");
  Serial.println();
  delay(1000); 
}
