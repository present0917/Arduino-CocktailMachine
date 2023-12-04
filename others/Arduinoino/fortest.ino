#include <Servo.h>

Servo myservo;

//모터드라이버 1
int IN1=1;
int IN2=2;
int IN3=3;
int IN4=4;
//모터드라이버 2
int IN5=5;
int IN6=6;
int IN7=7;
int IN8=8;
//모터드라이버 3
int IN9=9;
int IN10=10;
int IN11=11;
int IN12=12;






void setup() {
  myservo.attach(1);
  pinMode(A4,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  //Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(IN5,OUTPUT);
  pinMode(IN6,OUTPUT);
  pinMode(IN7,OUTPUT);
  pinMode(IN8,OUTPUT);
  pinMode(IN9,OUTPUT);
  pinMode(IN10,OUTPUT);
  pinMode(IN11,OUTPUT);
  pinMode(IN12,OUTPUT);

  
}
 
void loop() {
  // int button1=digitalRead(A4);
  // int button2=digitalRead(A3);
  // int button3=digitalRead(A2);
  // int button4=digitalRead(A1);
  // if(!button1)
  // {
  //   StartD();
  //   Serial.println("A");
  // }
  // else
  // {
  //   StopD();
  // }
  // if(!button2)
  // {
  //   StartF();
  //   Serial.println("B");
  // }
  // else
  // {
  //   StopF();
  // }
  // if(!button3)
  // {
  //   StartC();
  //   Serial.println("C");
  // }
  // else
  // {
  //   StopC();
  // }
  // if(!button4)
  // {
  //   stir();
  //   Serial.println("D");
  // }
  // else
  // {
  //   stirstop();
  // }
  int pos = 0;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  
  


  
  
  
  //6,7번 연결된 모터 1초 간격으로 껐다켜고
  //4,5번 연결된 모터도 동일하게
}
 
void stir(){
  myservo.write(60);
}
void stirstop(){
  myservo.write(90);
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
    digitalWrite(IN9,HIGH);
    digitalWrite(IN10,LOW);
}
void StopE()
{
    digitalWrite(IN9,LOW);
    digitalWrite(IN10,LOW);
}
void StartF()
{
    digitalWrite(IN11,HIGH);
    digitalWrite(IN12,LOW);
}
void StopF()
{
    digitalWrite(IN11,LOW);
    digitalWrite(IN12,LOW);
}