/*
콜라 A
보드카 B
우유 C
깔루아 D(PMW)
주스 E
그레나딘 F
*/
#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//온습도센서 (DHT sensor library by Adafruiit ver1.4.4)
#include <ArduinoJson.h>
//json 처리 위한 라이브러리
//ArduinoJson bt Benoit Balanchon Ver6.21.3

#include <Servo.h>
Servo myservo;
//서보모터

unsigned long pre;
unsigned long tempPreTime = 999999999;
int making = 0;

//모터드라이버 1
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
//모터드라이버 2
int IN5 = 6;
int IN6 = 7;
int IN7 = 8;
int IN8 = 9;

void temp()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    screw(0);
    return;
  }
  if(t>25)
  {
    milk();
    delay(500);
  }
  else if(h>60)
  {
    cock();
    delay(500);
  }
  else if(h>40)
  {
      screw(0);
      stir();
      stirstop();
  }
  else
  {
    screw(1);
     delay(500);
  }
  
}

void milk()
{
  Serial.print("cola");
  making=1;
  StartC();
  delay(2000);
  StopC();
  StartD(80);
  delay(8000);
  StopD();
  Serial.println(8);
  making=0;
  delay(500);
}

void screw(int num) {
  making = 1;
  StartB();
  delay(1500);
  StopB();
  StartE();
  delay(4000);
  StopE();
  if(num==1)
  {
    StartF();
    delay(500);
    StopF();
  }
  else{

  }
  
  Serial.println(8);
  making=0;
  delay(500);
}

void cock() {
  making = 1;
  StartB();
  delay(1500);
  StopB();
  StartA();
  delay(5000);
  StopA();
  
  Serial.println(8);
  making=0;
  delay(500);
}


void humidity() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
// Read temperature as Celsius (the default)

  // Read temperature as Fahrenheit (isFahrenheit = true)
  // 화씨 하려면 true 붙이라함
  // if (isnan(h) || isnan(t) ) {
  //   Serial.write(("Failed to read from DHT sensor!"));
  //   return;
  // }
  // int humi=h;
  // int celci=t;
  //dht11 공식문서 참고내용

  DynamicJsonDocument doc(1024);
  doc["h"] = h;
  doc["t"] = t;

  
  //수위센서 추가할부분
  doc["l"]= digitalRead(12);
  


  String jsonStr;
  serializeJson(doc, jsonStr);
  Serial.print(jsonStr);
  //arduinoJson 예제 중 StringExample 파일 참고.
}


void liquid() {
  // int humi=h;
  // int celci=t;
  //dht11 공식문서 참고내용

  DynamicJsonDocument doc(1024);
  
  
  //수위센서 추가할부분
  doc["l"]= digitalRead(12);
  


  String jsonStr;
  serializeJson(doc, jsonStr);
  Serial.print(jsonStr);
  //arduinoJson 예제 중 StringExample 파일 참고.
}


int command;
void setup() {
  Serial.begin(9600);
  myservo.attach(10);  //서보
  dht.begin();         //온습도센서
  pinMode(12, INPUT);  //수위센서


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  //모터드라이버
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  //버튼
}

void loop() {
  unsigned long time = millis();
  //첫 작동후 흘러가는 시간이 time이라는 변수에 저장된다.

  int button = digitalRead(A1);
  if (button == LOW && making == 0) {
    Serial.print(9);  //다음거 버튼누른다.
    delay(1000);      //없으면 너무 중복돼서 데이터가 가
  }
  //다음거시작

  int button2 = digitalRead(A0);
  if (button == LOW && making == 0) {
    Serial.print(8);  //완료신호 테스트용으로 둔거
    delay(1000);      
  }



  if (Serial.available()) {
    //서버에서 아두이노로 특정 data를 보내줬을때
    command = Serial.read();  //읽은거 command 저장
    //tempPreTime = time;
    if (command == '1') {
      Serial.print("screw");
       screw(0);
       stir();
       stirstop();
    }
    else if (command == '2') {
      Serial.print("sun");
      screw(1);
      delay(500);
    }
    else if (command == '3') {
      Serial.print("cola");
      cock();
      delay(500);
    }
    else if (command == '4') {
      milk();
      delay(500);
    }
    else if (command == '5') {
      temp();
      delay(500);
    }
    else if (command == '6') {
      stir();
      delay(500);
        stirstop();
        Serial.print(8); 
    }

  } 
  else if (time - pre >= 5000) {
    pre = time;//10초마다 갱신할수 있도록 장치작동시간과 지난번 센서측정시간을 비교
    humidity();
  }



  //  else if (time - tempPreTime >= 5000 && time - tempPreTime <= 5001) {
  //   digitalWrite(3, LOW);
  //   Serial.println(3);
  //   making=0;
  //  }
}

void stir(){
  myservo.write(60);
  delay(2000);
}
void stirstop(){
  myservo.write(90);
  delay(500);
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
void StartD(int num)
{
    digitalWrite(IN7,HIGH);
    digitalWrite(IN8,LOW);
    analogWrite(11,num);
}
void StopD()
{
    digitalWrite(IN7,LOW);
    digitalWrite(IN8,LOW);
}
void StartE()
{
    digitalWrite(A5,HIGH);
    digitalWrite(A4,LOW);
}
void StopE()
{
    digitalWrite(A5,LOW);
    digitalWrite(A4,LOW);
}
void StartF()
{
    digitalWrite(A3,HIGH);
    digitalWrite(A2,LOW);
}
void StopF()
{
    digitalWrite(A3,LOW);
    digitalWrite(A2,LOW);
}

