#include <WiFi.h>

const char* ssid = "xxxxxx";
const char* password = "xxxxxx";

void setup() {
	Serial.begin(115200);
	Serial.println();


	WiFi.softAP(ssid, password);
	IPAddress IP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(IP);


	Serial.println("Configurações do ponto de acesso:");
	Serial.print("SSID: ");
	Serial.println(ssid);
	Serial.print("Senha: ");
	Serial.println(password);
}

void loop() {

}
