#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "TEN_WIFI_CUA_BAN";
const char* pass = "MAT_KHAU_WIFI";

WebServer server(80);
const int LED_PIN = 2;
bool ledState = false;

void handleRoot() {
    String html = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>ESP32 LED Control</title></head><body>";
    html += "<h1>ESP32 Web Server - Pham Minh Hoang (25112214)</h1>";
    html += "<p>Trạng thái LED: <b>" + String(ledState ? "ĐANG BẬT" : "ĐANG TẮT") + "</b></p>";
    html += "<p><a href='/toggle'><button>Toggle (Đổi trạng thái)</button></a></p>";
    html += "<p><a href='/on'><button style='color:green;'>BẬT LED (/on)</button></a> ";
    html += "<a href='/off'><button style='color:red;'>TẮT LED (/off)</button></a></p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleToggle() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleOn() {
    ledState = true;
    digitalWrite(LED_PIN, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleOff() {
    ledState = false;
    digitalWrite(LED_PIN, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi đã kết nối!");
    Serial.print("Mở địa chỉ IP này trên trình duyệt: http://");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/toggle", handleToggle);
    server.on("/on", handleOn);
    server.on("/off", handleOff);
    server.begin();
}

void loop() {
    server.handleClient();
}
