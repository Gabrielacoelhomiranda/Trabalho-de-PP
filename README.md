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

### Código Principal- Emissor

#### Biblioteca e Definição de Constantes
* [Arq. Biblioteca e Constantes.txt](https://github.com/Gabrielacoelhomiranda/Trabalho-de-PP/files/14873696/Arq.Biblioteca.e.Constantes.txt)

#### Inicialização e conexão à rede WiFi- ESP32
* [Arq.ESP32.txt](https://github.com/Gabrielacoelhomiranda/Trabalho-de-PP/files/14873755/Arq.ESP32.txt)

####  Função de conexão ao broker MQTT
*  [Arq. Funções de Conexão MQTT.txt](https://github.com/Gabrielacoelhomiranda/Trabalho-de-PP/files/14873823/Arq.Funcoes.de.Conexao.MQTT.txt)
  
#### Execução Principal do Looping
* [Arq. Execução Loop.txt](https://github.com/Gabrielacoelhomiranda/Trabalho-de-PP/files/14873849/Arq.Execucao.Loop.txt)
