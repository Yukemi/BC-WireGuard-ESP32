#include <arduino.h>



unsigned long startTime;
unsigned long finishTime;

char ptrTaskList[128];

static const char* TAG0 = "timeMeasure";
static const char* TAG1 = "getCPUInfo";



void wgMonitor_timeReset() 
{
    startTime = millis();
}


void wgMonitor_timeMeasure(char* funcName) 
{
    finishTime = (millis() - startTime);

    ESP_LOGI(TAG0, "%s took %lu ms to load\n", funcName, finishTime);
    
    startTime = millis();
}

void wgMonitor_getCPUInfo() 
{
    ESP_LOGI(TAG1, "Free Heap:\t%lu bytes", ESP.getFreeHeap());
    ESP_LOGI(TAG1, "Temperature Read:\t%.2f °C", temperatureRead());
}



static void wgMonitor_getTaskInfo()
{
    vTaskList(ptrTaskList);
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));
}