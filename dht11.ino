
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define FIREBASE_HOST "https://dht22-370b1-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "DDh1wJOdgNYidNBEnulEeCpPEZ5rgHgDsSyyqzM7"
#define WIFI_SSID "SamrasingheWifi"
#define WIFI_PASSWORD "19570617"  


FirebaseData firebaseData;

void setup() {
  
  Serial.begin(9600);
  
  dht.begin();
  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  

  float t = dht.readTemperature();
  float h = dht.readHumidity();


  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT11 Sensor");
    return;
  }

  
  Serial.print("Temperature :");
  Serial.print(t);
  Serial.println(" *C");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println();


  if (Firebase.setFloat(firebaseData, "/Result_Reading/temperature", t)){
      Serial.println("Temperature sent");
    } else{
      Serial.println("Undeliverable temperature");
      Serial.println("Error: " + firebaseData.errorReason());
    } 
    
  if (Firebase.setFloat(firebaseData, "/Result_Reading/humidity", h)){
      Serial.println("Humidity sent");
      Serial.println();
    } else{
      Serial.println("Undeliverable humidity");
      Serial.println("Error: " + firebaseData.errorReason());
    }
    
  delay(1000);
}
