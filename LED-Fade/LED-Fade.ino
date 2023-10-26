int command;
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
  Serial.println(command);
  if(command==1)
  {
    digitalWrite(3,HIGH);
  }
  else if(command==2)
  {
    digitalWrite(4,HIGH);
  }
  else if(command==3)
  {
    digitalWrite(3,LOW);
  }
  else if(command==4)
  {
    digitalWrite(4,LOW);
  }

 //analogWrite(3, Serial.read());
}
