#define p 29
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  int input = analogRead(p);
  float volt = input*(3.3/4096);
  
  Serial.println(volt);
  delay(1000);
}
