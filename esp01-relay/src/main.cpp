#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

constexpr char WIFI_SSID[] = "Santiago";
constexpr char WIFI_PASSWORD[] = "KeepeR4Ever";

constexpr unsigned int UDP_PORT = 4210;

WiFiUDP udp;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected!");

    Serial.print("ESP-01S IP: ");
    Serial.println(WiFi.localIP());

    udp.begin(UDP_PORT);

    Serial.print("UDP listening on port ");
    Serial.println(UDP_PORT);
}

void loop()
{
    int packetSize = udp.parsePacket();

    if (packetSize > 0)
    {
        char buffer[32];

        int length = udp.read(buffer, sizeof(buffer) - 1);
        buffer[length] = '\0';

        Serial.print("Received: ");
        Serial.println(buffer);

        if (strcmp(buffer, "PING") == 0)
        {
            udp.beginPacket(udp.remoteIP(), udp.remotePort());
            udp.print("PONG");
            udp.endPacket();

            Serial.println("Sent: PONG");
        }
    }

    delay(10);
}