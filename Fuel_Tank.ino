// #include <stdlib.h>
// #include <EEPROM.h>
#define BLYNK_TEMPLATE_ID "TMPL2ApcD6E6Y"
#define BLYNK_TEMPLATE_NAME "ESP32Test"
#define BLYNK_AUTH_TOKEN "cGRStWkT64IO8Az9k3038-iQh2Y6br0Z"

#define BLYNK_PRINT Serial

#include <WiFiClient.h>
#include <Wifi.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "tones";
char pass[] = "67656868";


#include <Wire.h> 

#define relay A0
#define interval 1000 

const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 18; // Echo Pin of Ultrasonic Sensor
float temperature;
float pressure;
long  dist, dist2;
float dist2Percent;
float Percent;
int TankHeight;
int addr;

long dist_calc() { 
   long duration, dists;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   dists = duration / 29 / 2;
   return dists;
}

void setup() {
  Serial.begin(115200); 
  dist = dist_calc(); // Starting Serial Termina
  Serial.print("tankheight: ");
  Serial.print(dist);
  Serial.println(" cm");
  //EEPROM.write(addr, dist);
  //TankHeight =  EEPROM.read(addr);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  delay(4000);
}

void loop() {
  Blynk.run();
  
  calculate_depth();
  Blynk.virtualWrite(V4, Percent);
  Temperature();
  Blynk.virtualWrite(V2, temperature);
  Pressure();
  Blynk.virtualWrite(V3, pressure);
  Serial.print(pressure);
  Serial.print("hPa, "); 
  Serial.print(temperature);
  Serial.print("C");
  Serial.println();
  delay(2000);
   


}


void Temperature(){
  temperature = random(28, 34);
}

void Pressure(){
  pressure = random(1009, 1019);
}


void calculate_depth(){ 
      dist2 = dist_calc();
      dist2Percent = dist2 * 100 / dist;
      Percent = 100 - dist2Percent;
      Serial.print("tank level now at: "); 
      Serial.println(dist2);
      Serial.print("tank level for dist: ");
      Serial.print(dist);
      Serial.println(" cm");
      Serial.print(Percent);
      Serial.println(" %");
      delay(2000);
}
 




   
