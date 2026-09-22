#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

constexpr char WIFI_SSID[] = "Santiago";
constexpr char WIFI_PASSWORD[] = "KeepeR4Ever";

constexpr unsigned int UDP_PORT = 4210;
constexpr uint8_t RELAY_PIN = 0; // GPIO0

WiFiUDP udp;

void sendResponse(const char* message)
{
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.print(message);
    udp.endPacket();

    Serial.print("Sent: ");
    Serial.println(message);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Relay V4.0: active LOW.
    // Set the output HIGH to keep the relay OFF
    // after normal application startup.
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);

    Serial.println();
    Serial.println("ESP-01S starting...");

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
            sendResponse("PONG");
        }
        else if (strcmp(buffer, "RELAY_ON") == 0)
        {
            digitalWrite(RELAY_PIN, LOW);

            Serial.println("Relay ON");

            sendResponse("ACK:RELAY_ON");
        }
        else if (strcmp(buffer, "RELAY_OFF") == 0)
        {
            digitalWrite(RELAY_PIN, HIGH);

            Serial.println("Relay OFF");

            sendResponse("ACK:RELAY_OFF");
        }
    }

    delay(10);
}
