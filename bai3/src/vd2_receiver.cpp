#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

typedef struct {
    int dem;
    char message[32];
} GoiTin;

GoiTin goi;

void onRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&goi, incomingData, sizeof(goi));
    Serial.printf("Đã nhận từ MAC %02X:%02X:%02X:%02X:%02X:%02X -> Đếm: %d | Tin nhắn: %s\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], goi.dem, goi.message);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    Serial.print("Địa chỉ MAC của Receiver: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK) {
        Serial.println("Lỗi khởi tạo ESP-NOW!");
        return;
    }

    esp_now_register_recv_cb(esp_now_recv_cb_t(onRecv));
}

void loop() {
}
