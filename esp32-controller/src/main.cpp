#include <Arduino.h>
#include <WiFi.h>

constexpr char WIFI_SSID[] = "Santiago";
constexpr char WIFI_PASSWORD[] = "KeepeR4Ever";

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("Connecting to WiFi:");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);

        Serial.print(".");
        Serial.print(" status=");
        Serial.println(WiFi.status());

        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("================================");
        Serial.println("WiFi connected!");
        Serial.println("================================");

        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        Serial.print("Gateway: ");
        Serial.println(WiFi.gatewayIP());

        Serial.print("RSSI: ");
        Serial.println(WiFi.RSSI());
    }
    else
    {
        Serial.println("================================");
        Serial.println("WiFi connection FAILED");
        Serial.println("================================");

        Serial.print("Final status: ");
        Serial.println(WiFi.status());
    }
}

void loop()
{
    delay(1000);
}