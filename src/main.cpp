#include <Arduino.h> 
#include <WiFi.h> 
#include <WebServer.h>


WebServer server(80);

const int ledPin = 2; 
const char* SSID = "Victors Machine"; 
const char* password = "COOL12345"; 

String page(){
  return "<h1>hello world<h1>";
}

void handleRoot(){
   server.send(200, "text/html", page());
}

void setup() { 
  Serial.begin(115200); 
  delay(10); 
  
  WiFi.mode(WIFI_STA); 
  WiFi.begin(SSID, password); 
  
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){ 
    Serial.print("."); 
    delay(500); 
  } 
  
  Serial.printf("\nConnected to %s\n", SSID); 
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 

  
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  
  pinMode(ledPin, OUTPUT); 
  
  
  Serial.printf("chip: %s\n", ESP.getChipModel()); 
  Serial.printf("cores: %d\n", ESP.getChipCores()); 
  Serial.printf("frequency: %d MHz\n", ESP.getCpuFreqMHz()); 
  Serial.printf("setup() running on core %d\n", xPortGetCoreID()); 
} 

void loop() { 
  server.handleClient(); 

  
  digitalWrite(ledPin, HIGH); 
  delay(1000); 
  digitalWrite(ledPin, LOW); 
  delay(1000); 
}
