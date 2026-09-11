#include <Arduino.h>
#include <ESP8266WiFi.h>

constexpr char WIFI_SSID[] = "Santiago";
constexpr char WIFI_PASSWORD[] = "KeepeR4Ever";

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("ESP-01S starting...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi");

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected!");

        Serial.print("ESP-01S IP: ");
        Serial.println(WiFi.localIP());

        Serial.print("RSSI: ");
        Serial.println(WiFi.RSSI());
    }
    else
    {
        Serial.println("WiFi connection failed");
        Serial.print("Status: ");
        Serial.println(WiFi.status());
    }
}

void loop()
{
    delay(1000);
}