#include <Arduino.h>
#include <WiFi.h>

constexpr char WIFI_SSID[] = "Santiago";
constexpr char WIFI_PASSWORD[] = "KeepeR4Ever";

constexpr char ESP01_IP[] = "192.168.1.33";
constexpr unsigned int ESP01_PORT = 4210;

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

    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    Serial.println("Sending PING...");

    udp.beginPacket(ESP01_IP, ESP01_PORT);
    udp.print("PING");
    udp.endPacket();

    unsigned long start = millis();

    while (millis() - start < 2000)
    {
        int packetSize = udp.parsePacket();

        if (packetSize > 0)
        {
            char buffer[32];

            int length = udp.read(buffer, sizeof(buffer) - 1);
            buffer[length] = '\0';

            Serial.print("Received: ");
            Serial.println(buffer);

            break;
        }

        delay(10);
    }

    delay(3000);
}
