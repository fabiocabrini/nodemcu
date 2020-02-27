#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(10);
    // Conecta a rede WiFi
  WiFi.begin("NET_2GC89758", "B3C89758");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  // Imprime o endereco IP
  Serial.println(WiFi.localIP());

  EEPROM.begin(4); // Inicializa a EEPROM para a versao
}

void loop() {
  HTTPClient http;
  http.begin("192.168.0.25", 80, "/versao.txt");
    // inicio da conexao HTTP e envio do header
  if(http.GET() == 200) {
  uint8_t versao = EEPROM.read(0);
  uint8_t versaoSite = http.getString().toInt();
    Serial.printf("Versao Local: %d, Versao Remota: %d\n", versao, versaoSite);
    if (versaoSite != versao){
      EEPROM.write(0, versaoSite);
      EEPROM.commit();
      t_httpUpdate_return ret;
ret = ESPhttpUpdate.update("http://192.168.0.25/OTAhttpclient_blink.ino.nodemcu.bin");
      if (ret != HTTP_UPDATE_OK) {
        Serial.print("Falha na atualizacao: ");
  Serial.print(ESPhttpUpdate.getLastError());
        Serial.println(ESPhttpUpdate.getLastErrorString());
      }
    }
  }
  http.end();
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
}
