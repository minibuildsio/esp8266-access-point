#include <ESP8266WiFi.h>

#ifndef HEADER_HELPERFUNC
    #define HEADER_HELPERFUNC

    struct RequestHeader {
        char method[32] = "";
        char url[32] = "";
    };

    RequestHeader getHeader(WiFiClient client);
    void readToEndOfHeaders(WiFiClient client);
#endif