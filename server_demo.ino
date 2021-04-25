//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "webpageCode.h";
//------------------------------------------
ESP8266WebServer server(80);
const char* ssid = "TP-LINK_35A2";
const char* password = "58566633";
//------------------------------------------
void webpage()
{
  server.send(200, "text/html", webpageCode);
}
void led_control()
{
  String act_state = server.arg("state");
  Serial.println(act_state);
  if(act_state == "1")
    digitalWrite(LED_BUILTIN, LOW); 
  if(act_state == "2")
    digitalWrite(LED_BUILTIN, HIGH); 
}
//=================================================================
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  server.on("/", webpage);
  server.on("/led_set", led_control);
  server.begin();
}
//=================================================================
void loop()
{
  server.handleClient();

}
