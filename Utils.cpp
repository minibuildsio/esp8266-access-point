#include <ESP8266WiFi.h>
#include "Utils.h"

RequestHeader getHeader(WiFiClient client) {
  String method = client.readStringUntil(' ');
  String url = client.readStringUntil(' ');

  RequestHeader req;

  strcpy(req.method, method.c_str());
  strcpy(req.url, url.c_str());

  return req;
}

void readToEndOfHeaders(WiFiClient client) {
  client.find("\r\n\r\n");
}