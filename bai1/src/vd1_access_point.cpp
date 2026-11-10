#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "ESP32_AP_Nhom25112214";
const char* pass = "12345678";

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    WiFi.softAP(ssid, pass);
    Serial.println("=== ESP32 ACCESS POINT (AP) ===");
    Serial.print("SSID đã phát: ");
    Serial.println(ssid);
    Serial.print("Địa chỉ AP IP: ");
    Serial.println(WiFi.softAPIP());
}

void loop() {
}
