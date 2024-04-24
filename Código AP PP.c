#include <WiFi.h> // Inclui a biblioteca WiFi

const char* ssid = "xxxxxx";// SSID (nome da rede) do ponto de acesso
const char* password = "xxxxxx"; // Senha do ponto de acesso

void setup() {
	Serial.begin(115200); // Inicia a comunicação serial com uma taxa de transmissão de 115200 bps
	Serial.println();// Imprime uma nova linha na porta serial

	// Configura o ponto de acesso com o SSID e a senha especificados
	WiFi.softAP(ssid, password);
	IPAddress IP = WiFi.softAPIP();// Obtém o endereço IP do ponto de acesso
	Serial.print("AP IP address: ");
	Serial.println(IP);// Imprime o endereço IP do ponto de acesso


	// Imprime as configurações do ponto de acesso
	Serial.println("Configurações do ponto de acesso:");
	Serial.print("SSID: ");
	Serial.println(ssid);// Imprime o SSID do ponto de acesso
	Serial.print("Senha: ");
	Serial.println(password);// Imprime a senha do ponto de acesso
}

void loop() {
	// O loop está vazio, já que não há nenhuma operação contínua necessária 
}
