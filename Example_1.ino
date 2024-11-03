#include <Arduino.h>
#include "hitokoto.h"

const char* ssid = "Your_SSID"; // WiFi SSID
const char* password = "Your_Password"; // WiFi password
Hitokoto hitokoto;

void setup() 
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println("WiFi connected!");

    HitokotoResult res = hitokoto.getDetailHitokoto("https://v1.hitokoto.cn/?c=a&c=b&encode=json", 1, 2000);
    Serial.println(res.content);
    Serial.println(res.source);
    Serial.println(res.author);
}

void loop() 
{

}
