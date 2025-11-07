//Smart Notice Board
#include <ESP8266WiFi.h>
#include<ESP8266WiFiMulti.h>
#include<ESP8266HTTPClient.h>
#include<ESP8266WebServer.h>
#include <WiFiClient.h>
ESP8266WiFiMulti wifimulti;
HTTPClient http;
WiFiClient wificlient;
String link1,payload;
int httpcode;
#define IN1 16//
#define IN2 5
#define IN3 4
#define IN4 0




void setup() {
    pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  wifimulti.addAP("device2", "iot12345");
wifimulti.addAP("Airtel_IOT Lab 5G", "Iot@12345");
Serial.println("Connecting");
while(wifimulti.run()!=WL_CONNECTED)
{
Serial.println(".....");
delay(500);
}
Serial.println("Device name:");
Serial.print(WiFi.SSID());
Serial.println("IP Address:");
Serial.print(WiFi.localIP());
delay(1000);
  // put your setup code here, to run once:

}
void forwordMode() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

}

void backwordMode() {
   digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
 
}

void stopMode() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
void rightMode() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void leftMode() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void loop() {
  

 link1 = "http://192.168.1.19:5000/mode_status";
  http.begin(wificlient, link1);
  httpcode = http.GET();
  payload = http.getString();
  Serial.println(httpcode);
  Serial.println(payload);

  
    if (payload== "forward") {
      forwordMode();
    } else if (payload == "backword") {
      backwordMode();
    } else if (payload == "right") {
      rightMode();
    }
     else if (payload == "left") {
      leftMode();
    }
    else if(payload == "stop"){
      stopMode();
    }
   
  }




