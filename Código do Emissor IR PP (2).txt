#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ArduinoJson.h> 

#define IR_LED_PIN 23 // Defina o pino que o emissor IR está conectado

IRsend irsend(IR_LED_PIN); // Inicializa o emissor IR

// Configurações de WiFi e MQTT
const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxxx";
const char* mqtt_broker = "xxx.xxx.xx.x";
const char* topic = "esp32/test";
const char* mqtt_username = "xxxxx";
const char* mqtt_password = "xxxxx";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  irsend.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  client.setBufferSize(1024);
  connectToMqtt();
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  String messageTemp = String((char*)payload).substring(0, length);
  
  // Usa a ArduinoJson para parsear a string JSON
  StaticJsonDocument<1024> doc; // Ajuste o tamanho conforme necessário
  deserializeJson(doc, messageTemp);
  
  // Acessa o array dentro do objeto JSON
  JsonArray array = doc["teste"];
  
  JsonArray arr = doc["teste"].as<JsonArray>();

  // Criando um array para armazenar os números
  uint16_t numbers[arr.size()]; // Ajuste o tamanho do array conforme necessário

  // Extraindo os números do JsonArray
  size_t index = 0;
  for (int number : arr) {
    numbers[index++] = number;
    // Para demonstração, vamos imprimir cada número extraído
    //Serial.println(number);
  }

  Serial.println("Sending IR command...");
  irsend.sendRaw(numbers, index, 38);
  Serial.println("IR command sent.");
  delay(500);
}

void loop() {
  if (!client.connected()) {
    connectToMqtt();
  }
  client.loop();
}
