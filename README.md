
# Projeto de Controle Remoto MQTT com ESP32 e Home Assistant

Este projeto demonstra como utilizar um ESP32 para controlar dispositivos por infravermelho (IR) através de mensagens MQTT, com o servidor MQTT hospedado em um sistema operacional Home Assistant em uma Raspberry Pi 3. O ESP32 atua como um roteador em modo Access Point (AP), permitindo a conexão de outros dispositivos ESP32 que atuam como emissores IR. Os códigos infravermelho são armazenados e gerenciados pelo servidor Home Assistant.

## Funcionalidades:

 - Assistant em uma Raspberry Pi 3. Na raspberry foi instalado o sistema operacional home assistant (Linux) no qual hospedamos um servidor mqtt. Os comandos são enviados a partir de um serviço de publish mqtt acionados por uma interface feita no servidor, e recebidos pela ESP para serem enviados como comandos infraverrmelho. 
- Conexão de dispositivos ESP32 ao servidor MQTT em modo Access Point (AP) para envio e recebimento de comandos IR.
- Controle de dispositivos por infravermelho (como uma televisão) através de uma página web acessada via navegador em uma rede local.
- Armazenamento dos códigos IR(infravermelho) no servidor Home Assistan.

## Equipamentos necessários:

- ESP32 (pode ser um módulo como o NodeMCU-32S).
- Raspberry Pi 3 (ou superior) com sistema operacional Home Assistant instalado.
- Emissor IR (como o TSOP38238).
- LED IR(infravermelho).
- Resistores para o LED IR (se necessário, dependendo do modelo).
- Conexão com uma rede WiFi local. 

## Instruções de uso:
.................................................................................................

* ###  Código Principal- Emissor

*[Biblioteca e Definição de Constantes](#biblioteca-e-definição-de-constantes)*

*[Inicialização e conexão à rede WiFi-ESP32](#inicialização-e-conexão-à-rede-wifi-esp32)*

*[Função de conexão ao broker MQTT](#função-de-conexão-ao-broker-mqtt)*

*[Execução Principal do Looping](#execução-principal-do-looping)*


## Biblioteca e Definição de Constantes


                                            #include <Arduino.h>
                                            #include <WiFi.h>
                                            #include <PubSubClient.h>
                                            #include <IRremoteESP8266.h>
                                            #include <IRsend.h>
                                            #include <Base64.h>
                                            #include <ArduinoJson.h>

                                            #define IR_LED_PIN 23

                                            const char* ssid = "alecrim";
                                            const char* password = "jafalei3vezes";
                                            const char* mqtt_broker = "192.168.15.9";
                                            const char* topic = "esp32/test";
                                            const char* mqtt_username = "dedin";
                                            const char* mqtt_password = "dedin123";
                                            const int mqtt_port = 1883;


## Inicialização e conexão à rede WiFi-ESP32


                                            IRsend irsend(IR_LED_PIN);
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


##  Função de conexão ao broker MQTT


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


  
## Execução Principal do Looping


                                          void execucaoContinua() {
                                            if (!client.connected()) {
                                              connectToMqtt();
                                            }
                                            client.loop();
                                          }





## VÍDEO DO PROJETO



### Integrantes
-Beatriz Mayumi Maeda, Bianca Ferreira Freitas Torres, Gabriel Zuccolotto Alecrim, Gabriela Coelho Miranda, Mariana de Paula Ivo.







