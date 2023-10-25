#define p 29

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);
Serial1.write("AT+NAMEG2");

Serial1.read();
}

void loop() {
  // put your main code here, to run repeatedly: 
  Serial.println ("test ok ");
  delay(1000);
  Serial1.println ("test bluetooth ok ");
  delay(1000);


  int input = analogRead(p);
  float volt = input*(3.3/4096);
  
  Serial1.println(volt);
  delay(1000);
}


