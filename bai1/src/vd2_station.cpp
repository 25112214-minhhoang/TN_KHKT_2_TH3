#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "ESP32_AP_Nhom25112214";
const char* pass = "12345678";

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("=== ESP32 STATION (STA) ===");
    WiFi.begin(ssid, pass);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nKết nối thành công!");
    Serial.print("Địa chỉ IP nhận được: ");
    Serial.println(WiFi.localIP());
}

void loop() {
}
