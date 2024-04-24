// Inclusão das bibliotecas necessárias
#include <Arduino.h> // Biblioteca principal do Arduino
#include <WiFi.h> // Biblioteca para configuração e conexão Wi-Fi
#include <PubSubClient.h> // Biblioteca para comunicação MQTT
#include <IRremoteESP8266.h> // Biblioteca para controle de infravermelho
#include <IRsend.h> // Biblioteca para envio de sinais infravermelhos
#include <ArduinoJson.h> // Biblioteca para manipulação de JSON

#define IR_LED_PIN 23 // Define o pino ao qual o LED IR está conectado

IRsend irsend(IR_LED_PIN); // Cria uma instância do objeto IRsend para enviar comandos IR

// Definição das informações de rede e MQTT
const char* ssid = "xxxxx"; // Nome da rede Wi-Fi
const char* password = "xxxxx"; // Senha da rede Wi-Fi
const char* mqtt_broker = "xxxxx"; // Endereço do broker MQTT
const char* topic = "xxxxx"; // Tópico MQTT
const char* mqtt_username = "xxxxx"; // Nome de usuário MQTT
const char* mqtt_password = "xxxxx"; // Senha MQTT
const int mqtt_port = 1883; // Porta MQTT

WiFiClient espClient; // Cria uma instância do cliente Wi-Fi
PubSubClient client(espClient); // Cria uma instância do cliente MQTT

void setup() {
    Serial.begin(115200); // Inicializa a comunicação serial
    irsend.begin(); // Inicializa o envio de sinais IR
    WiFi.begin(ssid, password); // Conecta-se à rede Wi-Fi especificada

    // Aguarda até que a conexão Wi-Fi seja estabelecida
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Configura o servidor MQTT
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback); // Define a função de callback para mensagens MQTT recebidas
    client.setBufferSize(1024); // Define o tamanho do buffer MQTT
    connectToMqtt(); // Conecta-se ao broker MQTT
}

// Função para conectar-se ao broker MQTT
void connectToMqtt() {
    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32Client", mqtt_username, mqtt_password)) { // Tentativa de conexão MQTT
            Serial.println("Connected to MQTT");
            client.subscribe(topic); // Subscreve ao tópico MQTT
        }
        else {
            // Se falhar, imprime o motivo e tenta novamente após 5 segundos
            Serial.print("Failed to connect to MQTT: ");
            Serial.print(client.state());
            Serial.println(" Try again in 5 seconds");
            delay(5000);
        }
    }
}

// Função de callback chamada quando uma mensagem MQTT é recebida
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    // Converte o payload em uma String e cria um documento JSON
    String messageTemp = String((char*)payload).substring(0, length);
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, messageTemp);

    // Obtém o array de valores do campo "teste" do JSON
    JsonArray array = doc["teste"];
    JsonArray arr = doc["teste"].as<JsonArray>();

    // Cria um array de uint16_t e copia os valores do array JSON para ele
    uint16_t numbers[arr.size()];
    size_t index = 0;
    for (int number : arr) {
        numbers[index++] = number;
    }

    // Envia o comando IR com os valores do array
    Serial.println("Sending IR command...");
    irsend.sendRaw(numbers, index, 38);
    Serial.println("IR command sent.");
    delay(500);
}

void loop() {
    // Reconecta-se ao broker MQTT, se necessário, e mantém a comunicação
    if (!client.connected()) {
        connectToMqtt();
    }
    client.loop(); // Mantém a comunicação com o broker MQTT
}
