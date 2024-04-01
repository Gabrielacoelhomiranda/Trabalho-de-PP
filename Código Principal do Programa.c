//Código Principal

// Inclui as bibliotecas necessárias para funcionamento do projeto
#include <Arduino.h> // Biblioteca padrão do Arduino
#include <WiFi.h> // Biblioteca para conexão WiFi com ESP32
#include <PubSubClient.h> // Biblioteca para comunicação MQTT
#include <IRremoteESP8266.h> // Biblioteca para controle de dispositivos IR com ESP8266/ESP32
#include <IRsend.h> // Parte da biblioteca IRremote para enviar sinais IR
#include <Base64.h> // Biblioteca para codificação e decodificação Base64 (não usada explicitamente no código fornecido)
#include <ArduinoJson.h>  // Biblioteca para manipulação de JSON

// Define o pino conectado ao emissor IR
#define IR_LED_PIN 23

// Cria uma instância do emissor IR
IRsend irsend(IR_LED_PIN);

// Configurações da rede WiFi e MQTT
const char* ssid = "alecrim"; // Nome da rede WiFi
const char* password = "jafalei3vezes"; // Senha da rede WiFi
const char* mqtt_broker = "192.168.15.9"; // Endereço IP do broker MQTT
const char* topic = "esp32/test"; // Tópico MQTT ao qual o ESP32 se inscreve
const char* mqtt_username = "dedin"; // Nome de usuário para autenticação no broker MQTT (se necessário)
const char* mqtt_password = "dedin123"; // Senha para autenticação no broker MQTT (se necessário)
const int mqtt_port = 1883; // Porta para conexão com o broker MQTT

// Cliente WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Função setup, chamada uma vez na inicialização do ESP32
void setup() {
  Serial.begin(115200); // Inicia comunicação serial
  irsend.begin(); // Inicializa o emissor IR
  WiFi.begin(ssid, password); // Conecta à rede WiFi
  
  // Aguarda conexão com a rede WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Configura e conecta ao broker MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback); // Define a função de callback para mensagens MQTT
  client.setBufferSize(1024); // Define o tamanho do buffer para mensagens MQTT
  connectToMqtt(); // Tenta conectar ao broker MQTT
}

// Tenta conectar ao broker MQTT e inscrever-se no tópico especificado
void connectToMqtt() {
  if (!client.connected()) {
    String client_id = "esp32-client-" + String(WiFi.macAddress());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("MQTT broker connected");
      client.subscribe(topic);
    } else {
      Serial.print("Failed to connect to MQTT. State: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// Função chamada sempre que uma mensagem é recebida no tópico inscrito
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  // Converte o payload de byte para String
  String messageTemp = String((char*)payload).substring(0, length);
  
  // Deserializa o JSON recebido
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, messageTemp);
  
  // Acessa o array dentro do objeto JSON
  JsonArray arr = doc["teste"].as<JsonArray>();

  // Cria um array dinâmico para armazenar os números extraídos do JSON
  uint16_t numbers[arr.size()];

  // Extrai os números do JsonArray e armazena no array 'numbers'
  size_t index = 0;
  for (int number : arr) {
    numbers[index++] = number;
  }

  // Envia o comando IR
  Serial.println("Sending IR command...");
  irsend.sendRaw(numbers, index, 38); // Envia o sinal IR
  Serial.println("IR command sent.");
  delay(500); // Pequena pausa após enviar o comando
}

// Função loop, executa continuamente após o setup
void loop() {
  // Mantém a conexão MQTT ativa
  if (!client.connected()) {
    connectToMqtt();
  }
  client.loop(); // Processa qualquer mensagem recebida e mantém a conexão viva
}