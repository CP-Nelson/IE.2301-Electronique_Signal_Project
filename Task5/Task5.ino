void setup(){
  Serial.begin(9600);
  Serial.println("Begin Serial");
  Serial.println("Begin bluetooth");
  Serial1.begin(9600);
  Serial1.write("AT");
  Serial1.write("AT+NAMETHE_THREE_MASCKETERS");
  Serial1.read();
  }

void loop()
{
  if (Serial1.available()){
    Serial.println("TEST 1 = SOMETHING IS THERE TO COMMUNICATE");
    }
  else{
    Serial.println("Nothing");
    } 
  }
