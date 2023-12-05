#include "DHT.h"
#define DHTPIN 11
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

void stir() {
}

void makeone() {
  making = 1;
  digitalWrite(3, HIGH);
  delay(3000);
  digitalWrite(3, LOW);
  making = 0;
  Serial.println(8);
  delay(1000);
}

void maketwo() {
  making = 1;
  digitalWrite(4, HIGH);
  delay(3000);
  digitalWrite(4, LOW);
  making = 0;
  Serial.println(8);
  delay(1000);
}

void humidity() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.write(("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  // int humi=h;
  // int celci=t;
  //dht11 공식문서 참고내용

  DynamicJsonDocument doc(1024);
  doc["h"] = h;
  doc["t"] = t;

  /*
  //수위센서 추가할부분
  doc["l"]= digitalRead(12);
  */


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
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  //모터드라이버
  pinMode(A0, INPUT_PULLUP);
  //버튼
}

void loop() {
  unsigned long time = millis();
  //첫 작동후 흘러가는 시간이 time이라는 변수에 저장된다.

  int button = digitalRead(A0);
  if (button == LOW && making == 0) {
    Serial.print(9);  //다음거 버튼누른다.
    delay(1000);      //없으면 너무 중복돼서 데이터가 가
  }
  //다음거시작




  if (Serial.available()) {
    //서버에서 아두이노로 특정 data를 보내줬을때
    command = Serial.read();  //읽은거 command 저장
    //tempPreTime = time;
    if (command == '1') {
      makeone();
    } else if (command == '2') {
      maketwo();
    }
  } else if (time - pre >= 10000) {
    pre = time;//10초마다 갱신할수 있도록 장치작동시간과 지난번 센서측정시간을 비교
    humidity();
  }



  //  else if (time - tempPreTime >= 5000 && time - tempPreTime <= 5001) {
  //   digitalWrite(3, LOW);
  //   Serial.println(3);
  //   making=0;
  //  }
}
