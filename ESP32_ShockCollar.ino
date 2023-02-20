//https://dronebotworkshop.com/wifimanager/

#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
WiFiManager wm;

#include <ESPAsyncWebServer.h> //https://github.com/me-no-dev/ESPAsyncWebServer
AsyncWebServer server(80);

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
      request->send(200, "text/html", \
      "<head>\n\
<meta name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'>\n\
<title>meep chock</title>\n\
</head>\n\
<body bgcolor='black' text='white'>\n\
<center>\n\
<font size=7>🦊</font><br>\n\
<select name='action' id='action' onchange='return_to_last_value()'>\n\
<option value='0'>Shock</option>\n\
<option value='1' selected='selected'>Vibrate</option>\n\
<option value='2'>Sound</option>\n\
</select><br>\n\
<input type='range' min='1' max='100' value='50' class='slider' id='myRange'><br>\n\
<span id='demo'></span><br>\n\
<button type='button' onclick='submit()' value='OK'>OK</button>\n\
</body>\n\
<script>/*<![CDATA[*/var shock_value=0;var vibrate_value=0;var sound_value=0;var option=document.getElementById(\"action\");var slider=document.getElementById(\"myRange\");var output=document.getElementById(\"demo\");output.innerHTML=slider.value;slider.oninput=function(){if(option.value==0){shock_value=this.value}if(option.value==1){vibrate_value=this.value}if(option.value==2){sound_value=this.value}output.innerHTML=this.value};function submit(){fetch(\"/\",{method:\"POST\",headers:{Accept:\"application/x-www-form-urlencoded\",\"Content-Type\":\"application/x-www-form-urlencoded\"},body:\"i=\"+slider.value+\"&type=\"+action.value})}function return_to_last_value(){if(option.value==0){set_slider_value(shock_value);return}if(option.value==1){set_slider_value(vibrate_value);return}if(option.value==2){set_slider_value(sound_value);return}}function set_slider_value(a){slider.value=a;output.innerHTML=a};/*]]>*/</script>");
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

void int_to_bin_digit(unsigned int in, int count, int* out)
{
  unsigned int mask = 1U << (count - 1);
  int i;
  for (i = 0; i < count; i++) {
    out[i] = (in & mask) ? 1 : 0;
    in <<= 1;
  }
}

void command(int arr[], int _size) {
  bool b = true;
  for (int i = 0; i < _size; i++) {
    digitalWrite(txrfpin, b); delayMicroseconds(arr[i]);
    b = !b;
  }
}

void startSequenzPt1() {
  int arr[] = {1472, 730, 725, 231, 233, 720, 233, 720, 233, 719, 233, 720};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void startSequenzPt2() {
  int arr[] = {725, 231, 723, 230, 249, 720, 722, 231, 233, 720, 233, 720, 723, 231, 233, 719, 237, 719, 723, 231, 722, 231, 722, 231, 233, 731, 233, 719, 723, 230, 723, 231, 236, 720};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void endSequenz() {
  int arr[] = {723, 230, 723, 231, 722, 231, 722, 231, 233, 720, 232};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void _shock1() {
  int arr[] = {233, 719, 234, 719, 723, 231};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void _shock2() {
  int arr[] = {237, 719, 723, 231, 722, 231};
  command(arr, (sizeof(arr) / sizeof(int)));
}
void _vibrate1() {
  int arr[] = {233, 719, 722, 231, 233, 719};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void _vibrate2() {
  int arr[] = {725, 231, 233, 719, 722, 231};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void _sound1() {
  int arr[] = {723, 230, 233, 720, 233, 719};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void _sound2() {
  int arr[] = {725, 231, 722, 231, 233, 719};
  command(arr, (sizeof(arr) / sizeof(int)));
}

void executeTaskWithStrength(int i) {
  int digit[7];
  int_to_bin_digit(i, 7, digit);
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(txrfpin, 1); delayMicroseconds((digit[i] == 0) ? 230 : 730);
    digitalWrite(txrfpin, 0); delayMicroseconds((digit[i] == 0) ? 730 : 230);
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
    case (0):
      _shock1();
      intermezo(i);
      _shock2();
      break;
    case (1):
      _vibrate1();
      intermezo(i);
      _vibrate2();
      break;
    case (2):
      _sound1();
      intermezo(0);
      _sound2();
      break;
    default:
      _shock1();
      intermezo(i);
      _shock2();
  }
  endSequenz();
  digitalWrite(txrfpin, 0);
  delayMicroseconds(7877);
  digitalWrite(LED_BUILTIN, LOW);
}
