#define sensorPin PE_1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(sensorPin);
  float voltage = reading * (1.1/ 4095.0);
  float temperatureC = voltage/0.01;
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print("C  |  ");
  Serial.println();
  delay(1000); 
}
