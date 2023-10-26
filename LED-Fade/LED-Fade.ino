char command;
void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
}

void loop()
{
  while(!Serial.available());  
  command=Serial.read();
  if(command=='a')
  {
    digitalWrite(3,HIGH);
  }
  else if(command=='b')
  {
    digitalWrite(4,HIGH);
  }
  else if(command=='c')
  {
    digitalWrite(3,LOW);
  }
  else if(command=='d')
  {
    digitalWrite(4,LOW);
  }

 //analogWrite(3, Serial.read());
}
