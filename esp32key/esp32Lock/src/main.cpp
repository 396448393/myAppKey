#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <WiFiAP.h>

const char* ssid = "MyEsp32Lock";
const char* password = "Ljd&esp32Lock";

const String trueKey = "123123";

WebServer server(80);

const int led = 2;

String ledStatus = "close";//led 的状态

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}




/**
 * 接受json数据
*/
DynamicJsonDocument handlerPostJson() 
{
  DynamicJsonDocument jsonDoc(1024);
  if (server.method() == HTTP_POST) 
  {
    String jsonStr = server.arg("plain");
    deserializeJson(jsonDoc, jsonStr);
  }
  return jsonDoc;
}

/**
 * 开锁
*/
void openLock() {
  Serial.println("开锁");
  DynamicJsonDocument json = handlerPostJson();
  if(json.isNull()) {
    server.send(500, "text/plain", " POSTrequest ERROR! ");
    return;
  }
  String key = json["key"];
  Serial.println(key);
  if(trueKey.equals(key)) {
    ledStatus = "open";
    digitalWrite(led, 1);
    server.send(200, "text/plain", "open");
  } else {
    server.send(200, "text/plain", "error");
  }
  
}

/**
 * 关锁
*/
void closeLock() {
  Serial.println("关锁");
  DynamicJsonDocument json = handlerPostJson();
  if(json.isNull()) {
    server.send(500, "text/plain", " POSTrequest ERROR! ");
    return;
  }
  String key = json["key"];
  Serial.println(key);
  if(trueKey.equals(key)) {
    ledStatus = "close";
    digitalWrite(led, 0);
    server.send(200, "text/plain", "close");
  } else {
    server.send(200, "text/plain", "error");
  }
}

/**
 * 获取电平状态
*/
void getLockStatus() {
  DynamicJsonDocument json = handlerPostJson();
  if(json.isNull()) {
    server.send(500, "text/plain", " POSTrequest ERROR! ");
    return;
  }
  String key = json["key"];
  if(trueKey.equals(key)) {
    server.send(200, "text/plain", ledStatus );
  } else {
    server.send(200, "text/plain", "error");
  }
}

void testInline() {
  server.send(200, "text/plain", "works");
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  Serial.println("");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("");
  Serial.println("Server started");
  Serial.println("");

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/inline", testInline);
  server.on("/open", HTTP_POST, openLock);
  server.on("/close", HTTP_POST, closeLock);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
