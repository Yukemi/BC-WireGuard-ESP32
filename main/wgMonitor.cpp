#include <arduino.h>



unsigned long startTime;
unsigned long finishTime;

char ptrTaskList[128];



void wgMonitor_timeReset() 
{
    startTime = millis();
}


void wgMonitor_timeMeasure(char* funcName) 
{
    finishTime = (millis() - startTime);

    Serial.printf("[%s] took %lu ms to load\n", funcName, finishTime);
    
    startTime = millis();
}

void wgMonitor_getCPUInfo() 
{
    
    Serial.print("[getCPUInfo] Free Heap:\t");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");

    Serial.print("[getCPUInfo] Temperature Read:\t");
    Serial.print(temperatureRead());
    Serial.println(" °C");	
    
    // delay(1000);
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