#define Red_LED PF_1
#define Blue_LED PF_2
#define Green_LED PF_3

void setup() {
  // put your setup code here, to run once:
  pinMode(Red_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
  pinMode(Blue_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite(Blue_LED, HIGH);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, LOW); 
  delay(1000);
  digitalWrite(Blue_LED, LOW);   
  digitalWrite(Red_LED, HIGH); 
  digitalWrite(Green_LED, LOW); 
  delay(1000);
  digitalWrite(Blue_LED, LOW);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, HIGH); 
  delay(1000);
  digitalWrite(Blue_LED, LOW);   
  digitalWrite(Red_LED, HIGH); 
  digitalWrite(Green_LED, HIGH); 
  delay(1000);
  digitalWrite(Blue_LED, LOW);   
  digitalWrite(Red_LED, LOW); 
  digitalWrite(Green_LED, LOW); 
  delay(1000);
  
}
