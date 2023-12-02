#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//온습도센서 (DHT sensor library by Adafruiit ver1.4.4)


#include <ArduinoJson.h>
//json 처리 위한 라이브러리
//ArduinoJson bt Benoit Balanchon Ver6.21.3

unsigned long pre;
unsigned long tempPreTime=999999999;
int making=0;

void makeone(){
  making=1;
  digitalWrite(3,HIGH);
  delay(3000);
  digitalWrite(3,LOW);
  making=0;
  Serial.println(8);
  delay(1000);
}

void maketwo(){
  making=1;
  digitalWrite(4,HIGH);
  delay(3000);
  digitalWrite(4,LOW);
  making=0;
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


  //   Serial.print(celci);


DynamicJsonDocument doc(1024);
  doc["h"] = h;
  doc["t"] = t;
  String jsonStr;
  serializeJson(doc, jsonStr);
  Serial.print(jsonStr);
    //예제 중 StringExample 파일 참고.
 }


int command;
void setup() {
  Serial.begin(9600);
  dht.begin();  //온습도센서
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7,INPUT_PULLUP);
}

void loop() {
  int button=digitalRead(7);
  if(button==LOW && making==0){
      Serial.print(9); //다음거 버튼누른다.
      delay(1000); //없으면 너무 중복돼서 데이터가 가
  }
  unsigned long time=millis();
  //첫 작동후 흘러가는 시간이 time이라는 변수에 저장된다.

  // while(!Serial.available());

  if (Serial.available()) {
    //서버에서 아두이노로 특정 data를 보내줬을때
    command = Serial.read();

    
    tempPreTime=time; 
  if(command=='1')
  {
    makeone();
  }
  else if(command=='2')
  {
    maketwo();
  }
  }

  //  else if (time - tempPreTime >= 5000 && time - tempPreTime <= 5001) {
  //   digitalWrite(3, LOW);
  //   Serial.println(3);
  //   making=0;
  //  }
  


   else if (time - pre >= 10000) {
    pre=time;
    //1초마다 갱신할수 있도록 장치작동시간과 지난번 센서측정시간을 비교
    humidity();

    
 }


}
