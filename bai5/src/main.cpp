#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "TEN_WIFI_CUA_BAN";
const char* pass = "MAT_KHAU_WIFI";
const char* broker = "test.mosquitto.org";

const char* topic_pub = "bcse/th3/nhom-25112214/count";
const char* topic_sub = "bcse/th3/nhom-25112214/led";

const int LED_PIN = 2;
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
int value = 0;

void callback(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.printf("Nhận tin nhắn trên topic [%s]: %s\n", topic, message.c_str());

    if (message == "1") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("-> LED BẬT");
    } else if (message == "0") {
        digitalWrite(LED_PIN, LOW);
        Serial.println("-> LED TẮT");
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Đang kết nối MQTT Broker...");
        String clientId = "ESP32Client-25112214-" + String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
            Serial.println("Đã kết nối!");
            client.subscribe(topic_sub);
            Serial.printf("Đã subscribe topic: %s\n", topic_sub);
        } else {
            Serial.print("Thất bại, rc=");
            Serial.print(client.state());
            Serial.println(" Thử lại sau 5 giây...");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi đã kết nối!");

    client.setServer(broker, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000) {
        lastMsg = now;
        value++;
        String msg = String(value);
        Serial.printf("Publish tin nhắn [%s]: %s\n", topic_pub, msg.c_str());
        client.publish(topic_pub, msg.c_str());
    }
}
