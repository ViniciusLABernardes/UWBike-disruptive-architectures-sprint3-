#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

const char* BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char* ID_MQTT = "ancora3";
const char* TOPIC_PUBLISH = "fiap/iot/uwb/ancora3";

#define PIN_LED 15
#define PUBLISH_DELAY 10000
#define TAMANHO 200

WiFiClient espClient;
PubSubClient mqtt(espClient);
unsigned long publishUpdate = 0;
float dist_ancora3 = NAN;

void setupWiFi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado!");
}

void setupMQTT() {
  mqtt.setServer(BROKER_MQTT, BROKER_PORT);
}

void reconnectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (mqtt.connect(ID_MQTT)) {
      Serial.println(" conectado!");
    } else {
      Serial.println(" falha, tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  setupWiFi();
  setupMQTT();
  randomSeed(analogRead(0));
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) setupWiFi();
  if (!mqtt.connected()) reconnectMQTT();

  mqtt.loop();

  if (millis() - publishUpdate >= PUBLISH_DELAY) {
    publishUpdate = millis();
    dist_ancora3 = random(500, 2000) / 100.0;

    StaticJsonDocument<TAMANHO> doc;
    doc["distancia"] = dist_ancora3;
    doc["ancora"] = "ancora3";

    char buffer[TAMANHO];
    serializeJson(doc, buffer);

    mqtt.publish(TOPIC_PUBLISH, buffer);
    Serial.println(buffer);
  }
}