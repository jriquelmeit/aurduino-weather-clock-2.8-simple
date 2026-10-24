#pragma once

#include <Arduino.h>
#include <IPAddress.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "time_service.h"
#include "weather_service.h"

class DisplayUI {
public:
    DisplayUI(uint8_t cs, uint8_t dc, uint8_t rst, int8_t ledPin = -1);

    void begin(uint8_t rotation = 3);
    void showBootScreen(const char* ssid);
    void updateBootProgress(const char* stepMsg, uint8_t dots);

    // Dibuja la estructura base fija de la pantalla única
    void drawBaseLayout();

    // Actualizaciones dinámicas sin parpadeo (flicker-free)
    void updateTime(const DateTimeInfo& timeInfo);
    void updateDate(const DateTimeInfo& timeInfo);
    void updateWeather(const WeatherData& weather);
    void updateWifiStatus(bool connected, int rssi, const IPAddress& ip);
    void updateStatusBar(const char* message);

private:
    Adafruit_ILI9341 _tft;
    int8_t _ledPin;

    char _lastTimeStr[6];
    char _lastDateStr[40];
    char _lastDayName[16];
    int _lastSecond;
    int _lastRssi;
    bool _lastWifiState;

    void drawWeatherIcon(int x, int y, WeatherIconType type, bool small = false);
    void drawWaterDrop(int x, int y, uint16_t color);
    void drawWifiIndicator(int x, int y, bool connected, int rssi);
};
