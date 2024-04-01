#include <WiFi.h>

const char *ssid = "ppfinal";
const char *password = "senha";

void setup() {
  Serial.begin(115200);
  // Configurando a ESP32 como um ponto de acesso
  WiFi.softAP(ssid, password);

  Serial.println("Ponto de acesso iniciado");
  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Aqui você pode adicionar o código para manipular as conexões
}
