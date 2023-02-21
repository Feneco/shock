//https://dronebotworkshop.com/wifimanager/

#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
WiFiManager wm;

#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer
AsyncWebServer server(80);

#include "document.h"

//https://github.com/Johonis/arduino-pet-collar-control
#define shock   0
#define vibrate 1
#define sound   2

//esp32
#define txrfpin     13
#define LED_BUILTIN  2

void setup() {
    wm.setDebugOutput(false);
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(txrfpin, OUTPUT);
    pinMode(LED_BUILTIN,    OUTPUT);
    
    bool res;
    res = wm.autoConnect(); // auto generated AP name from chipid

    if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi
        Serial.println("Connected to " + WiFi.SSID() +" with IP " + ipToString(WiFi.localIP()));
        
        WiFi.softAP(ipToString(WiFi.localIP()).c_str()); //create a wifi network with the IP address as SSID to make it easier to find
        delay(15000);                                    //wait 15 seconds
        WiFi.softAPdisconnect(true);                     //disconnect the temporary network
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/html", htm);
    });
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request){
      int paramsNr = request->params();
      String pwr;
      String type;
      for(int i=0;i<paramsNr;i++){
          AsyncWebParameter* p = request->getParam(i);
          if(p->name() == "i"){
            pwr = p->value();
          }
          if(p->name() == "type"){
            type = p->value();
          }
      }
      switch (type.toInt()) {
        case (0):
          Serial.println("SHOCK " + (String)pwr.toInt());
          break;
        case (1):
          Serial.println("VIBRATE " + (String)pwr.toInt());
          break;
        case (2):
          Serial.println("SOUND " + (String)pwr.toInt());
          break;
        default:
          Serial.println("SHOCK " + (String)pwr.toInt());
      }
      for(int i=0;i<5;i++){
        execute(pwr.toInt(), type.toInt());
      }
      request->send(200, "text/plain", "OK");
    });
    server.begin();
}

void loop() {
  if(!digitalRead(0)){  //if BOOT button pressed
    Serial.println("Resetting WiFi...");
    wm.resetSettings(); //reset wifi credentials
    ESP.restart();      //restart the board
  }
}

String ipToString(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}

void command(const uint8_t* msg, const uint8_t& _size) {
  for (uint8_t c = _size - 1; c > -1; c--){
    for (uint8_t i = 0; i < size(uint8_t); i++) {
      digitalWrite(txrfpin, (msg[c] & (0b1 << i)) != 0);
      delayMicroseconds(233);
    }
  }
  digitalWrite(txrfpin, 0);
}

void startSequenzPt1() {
  uint8_t arr[] = {0x2, 0x22, 0x2e, 0x3f};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void startSequenzPt2() {
  uint8_t arr[] = {0x1, 0x77, 0x11, 0x77, 0x71, 0x17, 0x11, 0x71, 0x77};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void endSequenz() {
  uint8_t arr[] = {0x11, 0x77, 0x77};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void _shock1() {
  uint8_t arr[] = {0x7, 0x11};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void _shock2() {
  uint8_t arr[] = {0x7, 0x71};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}
void _vibrate1() {
  uint8_t arr[] = {0x1, 0x71};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void _vibrate2() {
  uint8_t arr[] = {0x7, 0x17};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void _sound1() {
  uint8_t arr[] = {0x1, 0x17};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void _sound2() {
  uint8_t arr[] = {0x1, 0x77};
  command(arr, (sizeof(arr) / sizeof(uint8_t)));
}

void executeTaskWithStrength(const int& s) {
  for (int i = 7; i >= 0; i--)
  {
    uint8_t v = (s & (0x1 << i))
    digitalWrite(txrfpin, 1); delayMicroseconds((v == 0) ? 233 : 730);
    digitalWrite(txrfpin, 0); delayMicroseconds((v != 0) ? 233 : 730);
  }
}

void intermezo(int i) {
  startSequenzPt2();
  executeTaskWithStrength(i);
}

void execute(int i, int type) {
  digitalWrite(LED_BUILTIN, HIGH);
  startSequenzPt1();
  switch (type) {
    case (sound):
      _sound1();
      intermezo(0);
      _sound2();
      break;
    case (shock):
      _shock1();
      intermezo(i);
      _shock2();
      break;    
    case (vibrate):
    default:
      _vibrate1();
      intermezo(i);
      _vibrate2();
      break;
  }
  endSequenz();
  digitalWrite(txrfpin, 0);
  delayMicroseconds(7877);
  digitalWrite(LED_BUILTIN, LOW);
}