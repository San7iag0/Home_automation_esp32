#include <Arduino.h>
#include <WiFi.h>

constexpr char WIFI_SSID[] = "YOUR_WIFI";
constexpr char WIFI_PASSWORD[] = "YOUR_PASSWORD";

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
}