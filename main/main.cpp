#include "Arduino.h"
#include "WireGuardTest.h"
#include "boardIni.h"
#include "wgMonitor.h"

extern "C" void app_main()
{
initArduino();
// pinMode(4, OUTPUT);
// digitalWrite(4, HIGH);
// Do your own thing

/* Setup */
boardIni();

wgMonitor_getCPUInfo();

wgMonitor_timeReset();
WiFiConnect();
wgMonitor_timeMeasure("WiFiConnect");
wgMonitor_getCPUInfo();

WireGuardIni();
wgMonitor_timeMeasure("WireGuardIni");
wgMonitor_getCPUInfo();

// wgTask_Create();
// wgMonitor_timeMeasure("WireGuardIni");
/* ===== */

/* Loop */
while (1)
{

}

/* ==== */
}