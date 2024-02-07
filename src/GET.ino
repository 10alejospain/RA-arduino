#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>


String serverName = "138.100.156.221:3000"; // IP address + port to connect to
const char* ssid     = "Javi";
const char* password = "12345678";
String nombreNodo = "Alejo";
float temperatura = 25.5;
float humedad = 68.2;
float co2 = 293;
float volatiles = 112;


serializeJson(doc, json);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(3000);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
 
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());

   


}

void loop() {
  // put your main code here, to run repeatedly:

   WiFiClient client;
   HTTPClient http;

   String serverPath = "http://" + serverName + "/record?id_nodo=" + nombreNodo + "&temperatura=" + temperatura + "&humedad=" + humedad + "&co2=" + co2 + "&volatiles=" + volatiles;

   http.begin(client, serverPath.c_str());
   // Send HTTP GET request
   int httpResponseCode = http.GET();
   
   if (httpResponseCode <= 0) {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
