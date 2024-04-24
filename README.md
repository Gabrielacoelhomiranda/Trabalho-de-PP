
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
  * *[Código do Receptor](#código-do-receptor)*

* ###  Vídeo
  * *[Vídeo do projeto](#vídeo-do-projeto)*
 
* ###  Participantes do Projeto
  * *[Integrantes](#integrantes)*
  
* ###  Bibliografia
  * *[Bibliografia](#bibliografia)*


#### Código do Emissor


                                                       #include <Arduino.h>
                                                       #include <WiFi.h>
                                                       #include <PubSubClient.h>
                                                       #include <IRremoteESP8266.h>
                                                       #include <IRsend.h>
                                                       #include <ArduinoJson.h> 

                                                       #define IR_LED_PIN 23 

                                                       IRsend irsend(IR_LED_PIN); 


                                                       const char* ssid = "xxxxx";
                                                       const char* password = "xxxxx";
                                                       const char* mqtt_broker = "xxxxx";
                                                       const char* topic = "xxxxx";
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

                                                       void connectToMqtt() {
                                                         while (!client.connected()) {
                                                           Serial.println("Connecting to MQTT...");
                                                           if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
                                                             Serial.println("Connected to MQTT");
                                                             client.subscribe(topic);
                                                           }else {
                                                            Serial.print("Failed to connect to MQTT: ");
                                                            Serial.print(client.state());
                                                            Serial.println(" Try again in 5 seconds");
                                                            delay(5000);
                                                           }
                                                          }
                                                        }

                                                        void callback(char* topic, byte* payload, unsigned int length) {
                                                          Serial.print("Message arrived in topic: ");
                                                          Serial.println(topic);

                                                          String messageTemp = String((char*)payload).substring(0, length);
                                                          StaticJsonDocument<1024> doc;
                                                          deserializeJson(doc, messageTemp);

                                                          JsonArray array = doc["teste"];
                                                          JsonArray arr = doc["teste"].as<JsonArray>();

                                                          uint16_t numbers[arr.size()];
                                                          size_t index = 0;
                                                          for (int number : arr) {
                                                            numbers[index++] = number;
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

#### Código do Roteador AP

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


#### Código do Receptor

                                                        esphome:
                                                         name: receptor_ir
                                                         friendly_name: receptor_ir

                                                        esp32:
                                                         board: esp32dev
                                                         framework:
                                                          type: arduino


                                                        logger:


                                                        ota:# Enable Home Assistant API
                                                         password: !secret ota_pwd

                                                        wifi:
                                                         ssid: "ppfinal"
                                                         password: "xxxx"

                                                         ap:# Enable fallback hotspot (captive portal) in case wifi connection fails
                                                         ssid: "xxxxx"
                                                         password: "xxxxx"

                                                       captive_portal:

                                                       remote_transmitter:
                                                        - pin: GPIO23
                                                        id: "D23"
                                                        carrier_duty_percent: 50%

                                                       api:
                                                        password: !secret api_pwd

                                                       remote_receiver:
                                                        pin:
                                                         inverted: True
                                                         number: GPIO01
                                                        dump: raw
                                                        tolerance: 100%


#### Vídeo do projeto
- https://youtu.be/1QRLDS0QRvs



### Integrantes
- Bianca Ferreira Freitas Torres, Gabriel Zuccolotto Alecrim, Gabriela Coelho Miranda, Mariana de Paula Ivo.

### Bibliografia

* Receptor: https://esphome.io/components/remote_receiver.html
* Emissor: https://github.com/crankyoldgit/IRremoteESP8266
* Roteador AP: https://randomnerdtutorials.com/esp32-access-point-ap-web-server/




