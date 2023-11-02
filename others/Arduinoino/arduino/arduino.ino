#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//온습도센서 (DHT sensor library by Adafruiit ver1.4.4)


#include <ArduinoJson.h>
//json 처리 위한 라이브러리
//ArduinoJson bt Benoit Balanchon Ver6.21.3

unsigned long pre;

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
}

void loop() {
  unsigned long time=millis();

  // while(!Serial.available());

  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command);
    if (command == 1) {
      digitalWrite(3, HIGH);
    } else if (command == 2) {
      digitalWrite(4, HIGH);
    } else if (command == 3) {
      digitalWrite(3, LOW);
    } else if (command == 4) {
      digitalWrite(4, LOW);
    }
  }

  
     //Serial.write("Test");
  //delay(1000);

  // Serial.write("Test");
  // delay(100);

   if (time - pre >= 1000) {
     pre=time;
    humidity();

     
   }


  //analogWrite(3, Serial.read());
}
