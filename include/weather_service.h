#pragma once

#include <Arduino.h>

enum WeatherIconType {
    ICON_SUNNY = 0,
    ICON_PARTLY_CLOUDY,
    ICON_CLOUDY,
    ICON_RAIN,
    ICON_SNOW,
    ICON_THUNDERSTORM,
    ICON_UNKNOWN
};

struct CurrentWeather {
    float temperature;
    int humidity;
    float uvIndex;
    int weatherCode;
    char conditionText[30];
    WeatherIconType iconType;
};

struct DailyForecast {
    char date[11];        // "YYYY-MM-DD"
    float tempMax;
    float tempMin;
    int weatherCode;
    int rainProbability;  // Probabilidad (%)
    float precipitation;  // Precipitación (mm)
    float uvIndexMax;     // UV Máximo del día
    char conditionText[30];
    WeatherIconType iconType;
};

struct WeatherData {
    bool valid;
    unsigned long lastFetchTime;
    CurrentWeather current;
    DailyForecast today;
};

const char* getWeatherDescription(int code);
WeatherIconType getWeatherIconType(int code);
const char* getUvCategory(float uv);
uint16_t getUvColor(float uv);

class WeatherService {
public:
    WeatherService();
    bool fetchWeather(const char* lat, const char* lon, WeatherData& outData);
};
