#include <Arduino.h>

void boardIni() {
    Serial.begin(115200);

    // delay(3000);

    while (!Serial && millis() < 5000 ) //Wait 5 seconds for Serial to initialize
    if (millis() > 5000) {
        Serial.println("[BoardIni] FAILED to initialize");
        break;
    }

    Serial.println("[BoardIni] Initiailized");
}