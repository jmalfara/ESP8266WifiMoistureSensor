#include "MoistureSensor.h"
#include "DebugMode.h"
#include "MD5/MD5.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define ZONE 3
#define ID 1
#define USERID "jmal"
#define HASHPASS "b44ef8c6b7de776b2276d9e0cf5e68d0"
#define BUTTON 4

String getUrl;
void sendHttpRequest();
void setupThreads();
void longClick();
void doubleClick();
void singleClick();
MoistureSensor mSensor = MoistureSensor(A0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Wifi Setup
  WiFi.begin("Rogers402","6DEDAEA7");
  /* Initialize Values from EEPROM */
  mSensor.getEEPROM();
  /* If main button is clicked on boot them put in bebug mode */
  DebugMode::startDebug(ZONE, ID, BUTTON, &mSensor);
}

void loop() {
  sendHttpRequest();
  Serial.println("Sleep");
  long seconds = 2
  ESP.deepSleep((1000000 * seconds),WAKE_RF_DEFAULT);
  delay(100);
  Serial.println("BAD");
}

String createHashPass() {
    String url = "https://192.168.0.15:5000/time";
    String serverTime = httpPost(url,"");
    char hashArray[255];
    String hashString = HASHPASS + serverTime;
    hashString.toCharArray(hashArray, 255);
    unsigned char* hash=MD5::make_hash(hashArray);
    //generate the digest (hex encoding) of our hash
    char *md5str = MD5::make_digest(hash, 16);
    //print it on our serial monitor
    String s = md5str;
    //Give the Memory back to the System if you run the md5 Hash generation in a loop
    free(md5str);
    free(hash);
    return s;
}

void sendHttpRequest() {
  HTTPClient http;
  String url = "https://192.168.0.15:5000/update";
  String post = "userid=";
  post += USERID;
  post += "&zone="; 
  post += ZONE;
  post += "&id=";
  post += ID;
  post += "&percent="; 
  post += mSensor.getPercent();
  post += "&hashpass=";
  post += createHashPass();
  Serial.println(mSensor.getPercent());
  Serial.println(httpPost(url, post));
}

String httpPost(String url, String post) {
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int code = http.POST(post);
  String response = "Error";
  if (code == 200) {
    response = http.getString();
  }
  http.end();
  return response;
}

