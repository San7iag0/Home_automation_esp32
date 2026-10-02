#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

constexpr char WIFI_SSID[] = "Santiago";
constexpr char WIFI_PASSWORD[] = "KeepeR4Ever";

constexpr unsigned int UDP_PORT = 4210;
constexpr uint8_t RELAY_PIN = 0; // GPIO0

WiFiUDP udp;

bool relayState = false;

// --------------------------------------------------
// Relay control
// --------------------------------------------------

void setRelay(bool state)
{
    relayState = state;

    // Relay is active LOW
    digitalWrite(RELAY_PIN, relayState ? LOW : HIGH);

    Serial.print("Relay state: ");
    Serial.println(relayState ? "ON" : "OFF");
}

// --------------------------------------------------
// UDP response
// --------------------------------------------------

void sendResponse(const char* message)
{
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write(message);
    udp.endPacket();

    Serial.print("Sent: ");
    Serial.println(message);
}

// --------------------------------------------------
// Command handling
// --------------------------------------------------

void handleCommand(const char* command)
{
    Serial.print("Received: ");
    Serial.println(command);

    if (strcmp(command, "PING") == 0)
    {
        sendResponse("PONG");
    }
    else if (strcmp(command, "RELAY_ON") == 0)
    {
        setRelay(true);
        sendResponse("ACK:RELAY_ON");
    }
    else if (strcmp(command, "RELAY_OFF") == 0)
    {
        setRelay(false);
        sendResponse("ACK:RELAY_OFF");
    }
    else if (strcmp(command, "GET_STATE") == 0)
    {
        sendResponse(relayState ? "STATE:ON" : "STATE:OFF");
    }
    else
    {
        sendResponse("ERROR:UNKNOWN_COMMAND");
    }
}

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup()
{
    Serial.begin(115200);
    delay(100);

    Serial.println();
    Serial.println("ESP-01S starting...");

    // Relay OFF during normal startup
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);

    relayState = false;

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

    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());

    udp.begin(UDP_PORT);

    Serial.print("UDP listening on port ");
    Serial.println(UDP_PORT);

    Serial.println("Relay initialized OFF");
}

// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop()
{
    int packetSize = udp.parsePacket();

    if (packetSize > 0)
    {
        char packet[128];

        int length = udp.read(packet, sizeof(packet) - 1);

        if (length > 0)
        {
            packet[length] = '\0';
            handleCommand(packet);
        }
    }
}
