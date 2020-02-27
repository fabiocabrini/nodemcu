#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup(void){

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println("Iniciando...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin("SSID", "PASSWORD");

  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin("SSID", "PASSWORD");
    Serial.println("Falha no Wifi, tentando novamente...");
  }

  httpUpdater.setup(&httpServer);
  httpServer.begin();

  Serial.print("HTTPUpdateServer pronto! V� para http://");
  Serial.print(WiFi.localIP());
  Serial.println("/update no seu navegador\n");
}

void loop(void){
  httpServer.handleClient();
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
}
