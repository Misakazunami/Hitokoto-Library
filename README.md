# Hitokoto Library

一个用于获取**一言(Hitokoto)**数据的库，适用于在Arduino IDE上开发ESP32\ESP8266。

A library for obtaining Hitokoto data, suitable for developing ESP32 \ ESP8266 on Arduino IDE.

## 目录  Index

- [Hitokoto Library](#hitokoto-library)
  - [目录  Index](#目录--index)
  - [特性  Feature](#特性--feature)
  - [导入库  Import Library](#导入库--import-library)
  - [使用示例  Example Usage](#使用示例--example-usage)
  - [许可证  Licence](#许可证--licence)

## 特性  Feature

- 支持ESP32/ESP8266    Support ESP32/ESP8266
- 基于Arduino IDE开发    Developed based on Arduino IDE
- 可以自定义API地址    Customized API address
- 可以获取一言的内容、出处和作者    Can obtain the content, source, and author of hitokoto
- 支持纯文本和JSON格式的返回    Supports returns in both plain text and JSON formats
- 简单易用的接口    Simple and easy-to-use interface

## 导入库  Import Library

1. 从Github上面下载源代码    Download the source code from GitHub
2. 将“hitokoto.h”复制到你的项目的文件夹内    Copy "hitokoto.h" to the folder of your project
3. 重新加载项目，此时应该出现头文件    Reload your project, header file should appear
4. 在你的主程序中引用该头文件    Reference the header file in your main Program

## 使用示例  Example Usage

```c_cpp
#include <Arduino.h>
#include "hitokoto.h"

const char* ssid = "BDAI"; // WiFi SSID
const char* password = "bdai@666"; // WiFi 密码

Hitokoto hitokoto; // 创建 Hitokoto 对象

void setup() 
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.println("连接中...");
    }
    Serial.println("WiFi已连接");

    HitokotoResult res = hitokoto.getDetailHitokoto("https://v1.hitokoto.cn/?c=a&c=b&encode=json", 1, 2000);
    Serial.println(res.content);
    Serial.println(res.source);
    Serial.println(res.author);
}

void loop() 
{
    // 主循环
}

```

## 许可证  Licence

本项目遵循GNU GPL V3许可

This project follows the GNU GPL V3 license
