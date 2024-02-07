/**
 * Redes Avanzadas
 * Modelo para peticiones GET y POST
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>


String serverName = "138.100.156.221:3000";
const char* ssid = "Javi";
const char* password = "12345678";
String nombreNodo = "Alejo";
float temperatura = 25.5;
float humedad = 68.2;
float co2 = 293;
float volatiles = 112;

String json;
StaticJsonDocument <2048> doc;

doc["id_nodo"] = nombreNodo;
doc["temperatura"] = temperatura;
doc["humedad"] = humedad;
doc["co2"] = co2;
doc["volatiles"] = volatiles;


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

   http.begin(client, "http://" + serverName + "/record");
   // Send HTTP GET request
   int httpResponseCode = http.POST(json);
   
   if (httpResponseCode <= 0) {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
