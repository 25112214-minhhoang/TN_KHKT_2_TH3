#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// Điền địa chỉ MAC của Receiver
uint8_t macNhan[] = {0x24, 0x0A, 0xC4, 0x00, 0x00, 0x00};

typedef struct {
    int dem;
    char message[32];
} GoiTin;

GoiTin goi;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Trạng thái gửi gói tin: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Thành công" : "Thất bại");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Lỗi khởi tạo ESP-NOW!");
        return;
    }

    esp_now_register_send_cb(OnDataSent);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, macNhan, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Lỗi thêm Peer!");
        return;
    }
}

void loop() {
    goi.dem++;
    snprintf(goi.message, sizeof(goi.message), "Hello from 25112214!");
    
    esp_now_send(macNhan, (uint8_t *)&goi, sizeof(goi));
    Serial.printf("Đang gửi đếm = %d\n", goi.dem);
    delay(2000);
}
