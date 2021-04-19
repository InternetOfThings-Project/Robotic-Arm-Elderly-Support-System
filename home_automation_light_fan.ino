
#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>

#define ssid "SamrasingheWifi"  //WiFi SSID
#define password "19570617"  //WiFi Password
#define FIREBASE_HOST "https://dht22-370b1-default-rtdb.firebaseio.com/"       //Firebase Project URL Remove "https:" , "\" and "/"
#define FIREBASE_AUTH "DDh1wJOdgNYidNBEnulEeCpPEZ5rgHgDsSyyqzM7"      //Firebase Auth Token

FirebaseData firebaseData;

int Device_1 = D1; //initialize D1 Pin
int Device_2 = D2;//itialize D2 Pin



void setup() {

  Serial.begin(9600);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(Device_1, OUTPUT); //initialize the Device OUTPUT
  pinMode(Device_2, OUTPUT); //initialize the Device OUTPUT

}

void loop() {

  if (Firebase.get(firebaseData, "/D1")) {
    if (firebaseData.dataType() == "string") {
      String De1 = firebaseData.stringData();
      if (De1 == "1") {
        digitalWrite(Device_1, LOW); //Device1 is ON
      }
      else if (De1 == "0") {
        digitalWrite(Device_2, HIGH); //Device1 if OFF
      }
    }
  }
  if (Firebase.get(firebaseData, "/D2")) {
    if (firebaseData.dataType() == "string") {
      String De1 = firebaseData.stringData();
      if (De1 == "1") {
        digitalWrite(Device_1, LOW); //Device1 is ON
      }
      else if (De1 == "0") {
        digitalWrite(Device_1, HIGH); //Device1 if OFF
      }
    }
  }

}
