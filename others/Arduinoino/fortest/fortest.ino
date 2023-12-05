#include <Servo.h>
Servo myservo;

//모터드라이버 1
int IN1=2;
int IN2=3;
int IN3=4;
int IN4=5;
//모터드라이버 2
int IN5=6;
int IN6=7;
int IN7=8;
int IN8=9;

void setup() {
  myservo.attach(10);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(IN5,OUTPUT);
  pinMode(IN6,OUTPUT);
  pinMode(IN7,OUTPUT);
  pinMode(IN8,OUTPUT);
  pinMode(12, INPUT);  //수위센서

  pinMode(A4,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);

  // pinMode(A4,OUTPUT);
  // pinMode(A3,OUTPUT);
  // pinMode(A2,OUTPUT);
  // pinMode(A1,OUTPUT);
}
 
void loop() {
  int button1=digitalRead(A4);
  int button2=digitalRead(A3);
  int button3=digitalRead(A2);
  int button4=digitalRead(A1);
  if(!button1)
  {
    // StartA();
    // one();
    Serial.println("ok");
  }
  else
  {
    // stop();
    // StopA();
  }
  if(!button2)
  {
    // StartB();
    // Serial.println("B");
  }
  else
  {
    // StopB();
  }
  if(!button3)
  {
     StartC();
     Serial.println("C");
  }
  else
  {
    StopC();
  }
  if(!button4)
  {
    // stir();
    // Serial.println("stir");
    
  }
  else
  {
    // stirstop();
    
  }
}
void stir(){
  myservo.write(30);
}
void stirstop(){
  myservo.write(90);
}

void stop()
{
    digitalWrite(IN7,HIGH);
    digitalWrite(IN8,LOW);
    analogWrite(11,0);
}
void one()
{
    digitalWrite(IN7,HIGH);
    digitalWrite(IN8,LOW);
    analogWrite(11,80);
}
void two()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(11,50);
}
void three()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(11,100);
}

void StartA()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
}
void StopA()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
}
void StartB()
{
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}
void StopB()
{
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}
void StartC()
{
    digitalWrite(IN5,HIGH);
    digitalWrite(IN6,LOW);
}
void StopC()
{
    digitalWrite(IN5,LOW);
    digitalWrite(IN6,LOW);
}
void StartD()
{
    digitalWrite(IN7,HIGH);
    digitalWrite(IN8,LOW);
}
void StopD()
{
    digitalWrite(IN7,LOW);
    digitalWrite(IN8,LOW);
}
void StartE()
{
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
}
void StopE()
{
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
}
void StartF()
{
    digitalWrite(A3,HIGH);
    digitalWrite(A4,LOW);
}
void StopF()
{
    digitalWrite(A3,LOW);
    digitalWrite(A4,LOW);
}