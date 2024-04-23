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
        }
        else {
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