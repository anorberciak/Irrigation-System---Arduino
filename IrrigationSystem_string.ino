#include "DHT.h"

#define DHT_PIN 52
#define DHT_TYPE DHT22
#define IN1 48
DHT dht22(DHT_PIN, DHT_TYPE);
const int min1SoilMoisture = 600;
const int max2SoilMoisture = 300;
const int mid1SoilMoisture = min1SoilMoisture-((min1SoilMoisture-max2SoilMoisture)/3);
const int mid2SoilMoisture = max2SoilMoisture+((min1SoilMoisture-max2SoilMoisture)/3);
int soilMoisture = 0;
int waterLevel = 0;
String str;
String pumpData;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  dht22.begin();
  pinMode(IN1,OUTPUT);
  digitalWrite(IN1,HIGH);
  pinMode(50,INPUT);
}
void loop() {
  delay(2000);
  float temperature = dht22.readTemperature();
  float humidity = dht22.readHumidity();
  if (isnan(temperature) || isnan(humidity)){
    Serial.println("Reading error from the DHT22 sensor!");
    return;
  }
  else{
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\t ");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\n ");
  }
  soilMoisture = analogRead(A2); // connect sensor to Analog
  Serial.print("Soil moisture: ");
  Serial.print(soilMoisture);
  Serial.print(" \t ");
  if(soilMoisture > mid1SoilMoisture && soilMoisture < min1SoilMoisture){
    Serial.print("Soil is dry\n");
    digitalWrite(IN1, LOW);
    delay(10000);
    digitalWrite(IN1, HIGH);
  }
  else{
    if(soilMoisture > mid2SoilMoisture && soilMoisture < mid1SoilMoisture){
     Serial.print("Soil is wet\n");
    }
    else{
      Serial.print("Soil is very Wet\n");
    }
  }
  delay(3000);
  waterLevel = digitalRead(50);
  Serial.print("water level: ");
  Serial.print(waterLevel);
  Serial.print("\n");
  int soilMoisturePercent = 100-((100*(soilMoisture-max2SoilMoisture))/(min1SoilMoisture-max2SoilMoisture));
  int temperatureInt = (int)temperature;
  int humidityInt = (int)humidity;
  str =String("temperature=")+String(temperatureInt)+String("&humidity=")+String(humidityInt)+String("&moisture=")+String(soilMoisturePercent)+String("&water=")+String(waterLevel);
  if ( Serial3.available()){ 
    Serial.println(str);
    Serial3.println(str);
    delay(5000);
    pumpData = Serial3.readString();
    Serial.println(pumpData);   
    if (pumpData.substring(13,20) == "Created") {
      Serial.print("Button: Turn on the water pump");
      digitalWrite(IN1, LOW);
      delay(10000);
      digitalWrite(IN1, HIGH);
    } 
    delay(5000);
  } 
}
