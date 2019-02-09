#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Utils.h"

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    delay(10);

    uint8_t mac[WL_MAC_ADDR_LENGTH];
    WiFi.softAPmacAddress(mac);
    boolean result = WiFi.softAP("ESP", "espkey123");
    if (result == true)
        Serial.println("Ready");
    else
        Serial.println("Failed!");

    IPAddress ip(192, 168, 1, 2);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0); 
    WiFi.config(ip, gateway, subnet);
    server.begin();

    delay(1000);
}

long timeLastMeasured = 0;

void loop()
{
    WiFiClient client = server.available();

    if (client)
    {
        Serial.println("New client");
        if (client.connected())
        {
            RequestHeader req = getHeader(client);

            Serial.println("Request:");
            Serial.println(req.method);
            Serial.println(req.url);

            readToEndOfHeaders(client);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
        
            client.println("Hello from ESP8266");
            
            client.println();
        }
        else
        {
            Serial.println("Client not connected.");
        }

        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}