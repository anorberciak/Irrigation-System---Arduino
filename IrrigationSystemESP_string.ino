#include <ESP8266WiFi.h>

String newData = " ";
const char* ssid = "";
const char* password = "";
const int httpPort = 9000;
const char* host = "";
WiFiClient client;
WiFiClient clientPump;

void setup() {  
  Serial.begin(115200);

  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
 if (Serial.available()) {  
  newData = Serial.readString();
  
  if (!client.connect(host, httpPort)) {
  }
  else{
    String url = "/?";
    url += newData;
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host:" + host + "\r\n" + "Connection: close\r\n\r\n");  
    String adres = String("GET ") + url + " HTTP/1.1\r\n" + "Host:" + host + "\r\n" + "Connection: close\r\n\r\n";
  } 
  delay(5000);
  if (!clientPump.connect(host, httpPort)) {
  }
  else{
    String url = "/turnOnOrOff";
    clientPump.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host:" + host + "\r\n" + "Connection: close\r\n\r\n");  
    String adres = String("GET ") + url + " HTTP/1.1\r\n" + "Host:" + host + "\r\n" + "Connection: close\r\n\r\n";
    String responseText = clientPump.readStringUntil('\r');
    Serial.print(responseText);   
  } 
  delay(5000);
 }              
}
