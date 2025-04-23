#include <HTTPClient.h>
#include <WireGuard-ESP32.h>
#include <WiFi.h>
#include "wgMonitor.h"
#include "WireGuardConfig.h"
#include "FreeRTOSConfig.h"



//========================
//    Wi-Fi Credentials    
//======================== 

/** For privacy sake
 * Config values defined in WireGuardConfig.h
 * local_ip(0,0,0,0);
 * 
 */

/* Why const char* ?
 * Puts just a pointer into the stack, saving space
 * char's contents is then put in the Static Memory
 * Stack         - Local variables, function calls, fast, limited space
 * Static Memory - Global variables, constants, limited space
*/

const char* ssid     = SSID;
const char* password = PASSWORD;

//========================
//    Wireguard Config    
//======================== 
/*  [Interface]
 * private_key   = Client Private Key
 * local_ip()    = ESP32 IP in tunnel
*/
const char* private_key = PRIVATE_KEY;
const IPAddress   local_ip(LOCAL_IP);

/*  [Peer]
 * public_key         = Server Public Key
 * endpoint_address   = Device Real IP
 * wg_endpoint_port   = Wireguard Port
 *
 * Endpoint is always the real IP 
*/
const char* public_key       = PUBLIC_KEY;
const char* endpoint_address = ENDPOINT_ADDRESS;
const int wg_endpoint_port   = WG_ENDPOINT_PORT;

//================================= 
//    Download/Upload Test Conf
//=================================
/* [Download]
 * server_url     = http://[endpoint_address]:[http_port]/[filename]
 * wg_server_url  = http://[wg_endpoint_address]:[http_port]/[filename]
*/ 
// const char* file_path            = FILE_PATH;
// const int http_endpoint_port     = HTTP_ENDPOINT_PORT;
// const char* wg_endpoint_address  = WG_ENDPOINT_ADDRESS;
// const int udp_endpoint_port      = UDP_ENDPOINT_PORT;
// const size_t payload_size        = PAYLOAD_SIZE;

// Wireguard client;
WireGuard wg;

// Wireguard task handle
TaskHandle_t wgTask_Handle;



void WiFiConnect() {
  WiFi.begin(ssid, password);
  Serial.print("[WiFiConnect] Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n[WiFiConnect] Connected");
    
  Serial.print("[WiFiConnect] Device IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("[WiFiConnect] Device IP in tunnel: ");
  Serial.println(local_ip.toString());
}



void WireGuardIni() {
  Serial.println("[WireGuardIni] Initializing");

  configTime(9 * 60 * 60, 0, "ntp.jst.mfeed.ad.jp", "ntp.nict.jp", "time.google.com");

  bool wgStatus = wg.begin(
    local_ip,
    private_key,
    endpoint_address,
    public_key,
    wg_endpoint_port
  );

  if (wgStatus != true) {
    Serial.println("[WireGuardIni] FAILED to initialize");
  }

  Serial.println("[WireGuardIni] Initialized");
}



void wgTask(void *param) {
  WireGuardIni();
  for(;;){
    wgMonitor_getCPUInfo();
    // wgMonitor_getTaskInfo();

    char ptrTaskList[128];

    vTaskList(ptrTaskList);
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));

    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void wgTask_Create() {
  xTaskCreate(
    wgTask,
    "WireGuard",
    4096,
    NULL,
    1,
    &wgTask_Handle
  );
}
