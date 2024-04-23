
# Projeto de Controle Remoto MQTT com ESP32 e Home Assistant

Este projeto tem como objetivo administrar dispositivos que operam por meio de tecnologia infravermelha através de uma interface de usuário baseada em navegador, implementada em uma rede local.

## Funcionalidades:

Uma ESP32 opera como um roteador no modo Access Point (AP), possibilitando que outros dispositivos ESP32 atuem como emissores e receptores de códigos IR (Infravermelho). Os códigos são armazenados e administrados pelo servidor Home Assistant, que está instalado em uma Raspberry Pi 3 com o sistema operacional Home Assistant (Linux). Este servidor também hospeda um servidor MQTT, por onde os comandos são enviados através de um serviço de publish MQTT, ativados por uma interface no servidor e recebidos pela ESP32, que os converte em comandos infravermelhos para comunicação entre os dispositivos.

## Equipamentos necessários:

- 3 ESP32 (pode ser um módulo como o NodeMCU-32S).
- Raspberry Pi 3 (ou superior) com sistema operacional Home Assistant instalado.
- Receptor IR(como TSOP38238).
- LED IR(infravermelho).
- Cabos jumpers. 

* ###  Projeto
  * *[Código do Emissor](#código-do-emissor)*
  * *[Código do Roteador AP](#código-do-roteador-ap)*
  * *[Biblioteca e Definição de Constantes](#biblioteca-e-definição-de-constantes)*
  * *[Inicialização e conexão à rede WiFi-ESP32](#inicialização-e-conexão-à-rede-wifi-esp32)*
  * *[Função de conexão ao broker MQTT](#função-de-conexão-ao-broker-mqtt)*
  * *[Execução Principal do Looping](#execução-principal-do-looping)*
* ###  Vídeo
  * *[Vídeo do projeto](#vídeo-do-projeto)*
 




#### Código do Emissor

#### Código do Roteador AP


#### Biblioteca e Definição de Constantes


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


#### Inicialização e conexão à rede WiFi-ESP32


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


####  Função de conexão ao broker MQTT


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


  
#### Execução Principal do Looping


                                          void execucaoContinua() {
                                            if (!client.connected()) {
                                              connectToMqtt();
                                            }
                                            client.loop();
                                          }


#### Vídeo do projeto
- https://youtu.be/1QRLDS0QRvs



### Integrantes
- Bianca Ferreira Freitas Torres, Gabriel Zuccolotto Alecrim, Gabriela Coelho Miranda, Mariana de Paula Ivo.





