#include <Arduino.h>

static const char* TAG = "boardIni";



void boardIni() {
    Serial.begin(115200);

    // delay(3000);

    while (!Serial && millis() < 5000 ) //Wait 5 seconds for Serial to initialize
    if (millis() > 5000) {
        ESP_LOGE(TAG, "FAILED to initialize");
        break;
    }
    
    ESP_LOGI(TAG, "Initialized");
}