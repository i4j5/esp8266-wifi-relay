#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266SSDP.h>
#include <FS.h>
#include <ArduinoJson.h>

IPAddress apIP(192, 168, 4, 1);
ESP8266WebServer HTTP(80);
File fsUploadFile;

String wifi_ssid = "";
String wifi_pass = "";
String devece_name = "esp8266WifiRelay";
String devece_id = "";
String devece_key = "";
String jsonConfig = "{}";
char *server = "192.168.1.254"; 

void setup() {
  Serial.begin(115200);
  pinMode(5, INPUT);
  
  Serial.println("");
  
  //Запускаем файловую систему
  Serial.println("Start 4-FS");
  FS_init();
  
  Serial.println("Step7-FileConfig");
  loadConfig();
  
  Serial.println("Start 1-WIFI");
  //Запускаем WIFI
  WIFIinit();
  
  //Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start 3-SSDP");
  SSDP_init();
  
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 2-WebServer");
  HTTP_init();

}

void loop() {
  HTTP.handleClient();
  delay(1);
  myServer();
}

void myServer() {
  WiFiClient client;
  int port = 80;
  String host = "Host: ";
  host.concat(server);
  if (!client.connect(server, port)) {
    Serial.println("connection failed");
    return;
  } else {
    //http://192.168.1.254/?custom=1&cmd=1001
    client.println("GET /?custom=1&cmd=1001" + "HTTP/1.1");
    client.println(host);
    client.println("Connection: close");
    client.println();
    
//    delay(500);
    
//    while(client.available()){
//      String line = client.readStringUntil('\n');
//       
//      //if (line == "true" || line == "false") {
//        Serial.print('\n');
//      //}
//      
//      if (line == "true") {
//        digitalWrite(5, HIGH);
//        Serial.print("on"); 
//      }
//      
//      if (line == "false"){
//         digitalWrite(5, LOW);
//         Serial.print("off"); 
//      }
//    }
  }
}




