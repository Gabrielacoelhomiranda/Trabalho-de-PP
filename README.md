Projeto de Controle Remoto MQTT com ESP32 e Home Assistant

Este projeto demonstra como utilizar um ESP32 para controlar dispositivos por infravermelho (IR) através de mensagens MQTT, com o servidor MQTT hospedado em um sistema operacional Home Assistant em uma Raspberry Pi 3. O ESP32 atua como um roteador em modo Access Point (AP), permitindo a conexão de outros dispositivos ESP32 que atuam como emissores IR. Os códigos infravermelho são armazenados e gerenciados pelo servidor Home Assistant.

Funcionalidades:

Configuração de um servidor MQTT hospedado no sistema operacional Home Assistant em uma Raspberry Pi 3.
Conexão de dispositivos ESP32 ao servidor MQTT em modo Access Point (AP) para envio e recebimento de comandos IR.
Controle de dispositivos por infravermelho (como uma televisão) através de uma página web acessada via navegador em uma rede local.
Armazenamento dos códigos IR no servidor Home Assistant para fácil gerenciamento e integração com outros dispositivos e automações.
Componentes necessários:

ESP32 (pode ser um módulo como o NodeMCU-32S).
Raspberry Pi 3 (ou superior) com sistema operacional Home Assistant instalado.
Emissor IR (como o TSOP38238).
LED IR.
Resistores para o LED IR (se necessário, dependendo do modelo).
Conexão com uma rede WiFi local.
Bibliotecas necessárias:

WiFi.h
PubSubClient.h
IRremoteESP8266.h
IRsend.h
Base64.h (não usada explicitamente no código fornecido)
ArduinoJson.h
Instruções de uso:

Instale e configure o sistema operacional Home Assistant em sua Raspberry Pi 3.
Configure um servidor MQTT no Home Assistant para comunicação entre dispositivos.
Monte o circuito do ESP32 com o emissor IR conforme as especificações do fabricante.
Carregue o código fornecido neste repositório no seu ESP32 utilizando a IDE do Arduino.
Modifique as configurações de rede WiFi (SSID e senha) e do servidor MQTT (endereço IP, porta, tópico, nome de usuário e senha, se necessário) de acordo com sua configuração.
Compile e faça o upload do código para o ESP32.
Certifique-se de que o servidor MQTT do Home Assistant está em execução e acessível pela rede.
Conecte-se à rede Wi-Fi do ESP32 (modo AP) a partir de um dispositivo cliente.
Acesse a página web hospedada no ESP32 através de um navegador em sua rede local.
Envie comandos através da página web para controlar dispositivos por infravermelho. Esses comandos serão transmitidos via MQTT para o servidor Home Assistant, que irá gerenciar os códigos IR e enviá-los para o dispositivo ESP32 correspondente.
Observações:

Este projeto requer conhecimentos básicos de configuração de rede, MQTT e programação em Arduino.
Certifique-se de ajustar as configurações do código conforme sua rede e servidor MQTT do Home Assistant.
A integração com o Home Assistant permite uma ampla gama de possibilidades de automação e controle de dispositivos domésticos.
Este projeto pode ser expandido para incluir mais funcionalidades, como a adição de sensores para feedback de estado dos dispositivos controlados por IR.


Autores:

Beatriz Mayumi Maeda, Bianca Ferreira Freitas Torres, Gabriel Zuccolotto Alecrim, Gabriela Coelho Miranda, Mariana de Paula Ivo 


Licença:
Este projeto está disponível sob a licença [especificar a licença, se houver]. Sinta-se à vontade para usar, modificar e distribuir este código conforme necessário.


