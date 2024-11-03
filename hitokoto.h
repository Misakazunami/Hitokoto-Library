// 适用于ESP32，ESP8266的一言库
// Hitokoto library, applicable to ESP32, ESP8266
// Development environment: Arduino IDE
// 作者： MisakaZunami
// Author: MisakaZunami
// 更新时间：2024/11/2
// Last updated: 2024/11/2
#ifndef _HITOKOTO_H
#define _HITOKOTO_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>                                      // 如要使用ESP8266，请注释此段 If using ESP8266, comment this line
// #include <ESP8266WiFi.h>                            // 如要使用ESP8266，请取消注释此段 If using ESP8266, uncomment this line
#include <ArduinoJson.h>

// 定义基础URL
// Define the base URL
const char* BASE_URL = "https://v1.hitokoto.cn/";

// 定义结构体用于保存一言详细信息
// Structure used to save detailed information about hitokoto
struct HitokotoResult 
{
    String content; // 一言内容
    String source;  // 出处
    String author;  // 作者
};

/**
 * Hitokoto类用于获取一言（hitokoto）数据
 * Hitokoto class for retrieving hitokoto data
 */
class Hitokoto 
{
public:
    // 构造函数
    // Constructor
    Hitokoto() : hitokoto("") 
    {
        // 默认API设置
        // Default API settings
        setApi('a', 'j', 'u'); // 使用字符而不是字符串
        // Use characters instead of strings
    }

    /**
     * 设置API参数
     * Set API parameters
     * @param kind 类别参数
     * @param encode 编码参数
     * @param decode 解码参数
     * @param kind Category parameter
     * @param encode Encoding parameter
     * @param decode Decoding parameter
     */
    void setApi(char kind, char encode, char decode) 
    {
        Hitokoto_API = String(BASE_URL) + "?c=" + kind + "&encode=" + encode + "&decode=" + decode;
    }

    /**
     * 获取一言数据
     * Retrieve hitokoto data
     * @return 一言字符串
     * @return Hitokoto string
     */
    String getHitokoto()
    {
        HTTPClient http;
        http.begin(Hitokoto_API);
        int httpCode = http.GET();

        if (httpCode > 0) 
        {
            String payload = http.getString();
            deserializeJson(jsonDoc, payload); // 反序列化JSON响应
            // Deserialize the JSON response
            hitokoto = jsonDoc["hitokoto"].as<String>(); // 获取'hitokoto'字段
            // Get the 'hitokoto' field
        } else 
        {
            Serial.printf("HTTP GET请求失败，代码：%d\n", httpCode);
            // HTTP GET request failed, code: %d
        }
        http.end();
        return hitokoto;
    }

    /**
     * 获取自定义API的一言数据
     * Retrieve hitokoto data from a custom API
     * @param customApi 自定义的API地址
     * @param times 请求次数，默认为1
     * @param delaytime 每次请求后的延迟时间，默认为2000毫秒
     * @return 请求结果的字符串
     * @param customApi Custom API address
     * @param times Number of requests, default is 1
     * @param delaytime Delay time after each request, default is 2000 milliseconds
     * @return Result string of the request
     */
    String getCustomHitokoto(String customApi, int times, int delaytime) 
    {
        String result = "";
        for (int i = 0; i < times; i++) 
        {
            HTTPClient http;
            http.begin(customApi);
            int httpCode = http.GET();

            if (httpCode > 0) 
            {
                String payload = http.getString();
                result += payload + "\n"; // 收集结果
                // Collect results
            } else 
            {
                Serial.printf("自定义HTTP GET请求失败，代码：%d\n", httpCode);
                // Custom HTTP GET request failed, code: %d
            }
            http.end();
            delay(delaytime);
        }
        return result;
    }

    /**
     * 获取自定义API的一言详细数据
     * Retrieve hitokoto data from a custom API
     * @param customApi 自定义的API地址
     * @param times 请求次数，默认为1
     * @param delaytime 每次请求后的延迟时间，默认为2000毫秒
     * @return HitokotoResult 结构体，包含内容、出处和作者
     * @param customApi Custom API address
     * @param times Number of requests, default is 1
     * @param delaytime Delay time after each request, default is 2000 milliseconds
     * @return HitokotoResult structure containing content, source, and author
     */
    HitokotoResult getDetailHitokoto(String customApi, int times, int delaytime) 
    {
        HitokotoResult result;
        result.content = "";
        result.source = "";
        result.author = "";

        for (int i = 0; i < times; i++) 
        {
            HTTPClient http;
            http.begin(customApi);
            int httpCode = http.GET();

            if (httpCode > 0) 
            {
                String payload = http.getString();
                deserializeJson(jsonDoc, payload); // 反序列化JSON响应
                result.content += jsonDoc["hitokoto"].as<String>(); // 获取内容
                result.source += jsonDoc["from"].as<String>();    // 获取出处
                result.author += jsonDoc["from_who"].as<String>();    // 获取作者
            } 
            else 
            {
                Serial.printf("自定义HTTP GET请求失败，代码：%d\n", httpCode);
            }
            http.end();
            delay(delaytime);
        }
        return result; // 返回结果结构体
    }

    /**
     * 获取文本类型的一言数据
     * Retrieve text type hitokoto data
     * @return 一言字符串
     * @return Hitokoto string
     */
    String getHitokotoText() 
    {
        HTTPClient http;
        http.begin(String(BASE_URL) + "?c=a&c=b&encode=text");
        int httpCode = http.GET();

        if (httpCode > 0) 
        {
            hitokoto = http.getString();
        } else 
        {
            Serial.printf("文本HTTP GET请求失败，代码：%d\n", httpCode);
            // Text HTTP GET request failed, code: %d
        }
        http.end();
        return hitokoto;
    }

private:
    String hitokoto;
    String Hitokoto_API;
    JsonDocument jsonDoc;
};

#endif
