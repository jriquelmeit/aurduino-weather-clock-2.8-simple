#include "weather_service.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>

const char* getWeatherDescription(int code) {
    switch (code) {
        case 0:  return "Despejado";
        case 1:  return "Mayormente claro";
        case 2:  return "Parcialmente nublado";
        case 3:  return "Nublado";
        case 45:
        case 48: return "Niebla";
        case 51: return "Llovizna ligera";
        case 53: return "Llovizna moderada";
        case 55: return "Llovizna densa";
        case 56:
        case 57: return "Llovizna helada";
        case 61: return "Lluvia ligera";
        case 63: return "Lluvia moderada";
        case 65: return "Lluvia fuerte";
        case 66:
        case 67: return "Lluvia helada";
        case 71: return "Nieve ligera";
        case 73: return "Nieve moderada";
        case 75: return "Nieve fuerte";
        case 77: return "Granizo de nieve";
        case 80: return "Chubascos ligeros";
        case 81: return "Chubascos moderados";
        case 82: return "Chubascos fuertes";
        case 85:
        case 86: return "Chubascos de nieve";
        case 95: return "Tormenta";
        case 96:
        case 99: return "Tormenta con granizo";
        default: return "Variable";
    }
}

WeatherIconType getWeatherIconType(int code) {
    switch (code) {
        case 0:
        case 1:
            return ICON_SUNNY;
        case 2:
            return ICON_PARTLY_CLOUDY;
        case 3:
        case 45:
        case 48:
            return ICON_CLOUDY;
        case 51:
        case 53:
        case 55:
        case 56:
        case 57:
        case 61:
        case 63:
        case 65:
        case 66:
        case 67:
        case 80:
        case 81:
        case 82:
            return ICON_RAIN;
        case 71:
        case 73:
        case 75:
        case 77:
        case 85:
        case 86:
            return ICON_SNOW;
        case 95:
        case 96:
        case 99:
            return ICON_THUNDERSTORM;
        default:
            return ICON_PARTLY_CLOUDY;
    }
}

const char* getUvCategory(float uv) {
    if (uv < 3.0f) return "Bajo";
    if (uv < 6.0f) return "Mod.";
    if (uv < 8.0f) return "Alto";
    if (uv < 11.0f) return "M.Alto";
    return "Extr.";
}

uint16_t getUvColor(float uv) {
    if (uv < 3.0f) return ILI9341_GREEN;
    if (uv < 6.0f) return ILI9341_YELLOW;
    if (uv < 8.0f) return ILI9341_ORANGE;
    if (uv < 11.0f) return ILI9341_RED;
    return ILI9341_MAGENTA;
}

WeatherService::WeatherService() {}

bool WeatherService::fetchWeather(const char* lat, const char* lon, WeatherData& outData) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(F("[Clima] Error: Wi-Fi desconectado"));
        return false;
    }

    WiFiClient client;
    HTTPClient http;
    http.setTimeout(7000);

    String url = "http://api.open-meteo.com/v1/forecast?latitude=";
    url += lat;
    url += "&longitude=";
    url += lon;
    url += "&current=temperature_2m,relative_humidity_2m,weather_code,uv_index";
    url += "&daily=weather_code,temperature_2m_max,temperature_2m_min,precipitation_probability_max,precipitation_sum,uv_index_max";
    url += "&forecast_days=1";
    url += "&timezone=auto";

    Serial.print(F("[Clima] Consultando Open-Meteo: "));
    Serial.println(url);

    if (!http.begin(client, url)) {
        Serial.println(F("[Clima] Error: fallo al iniciar HTTP"));
        return false;
    }

    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
        Serial.printf("[Clima] Error HTTP: %d\n", httpCode);
        http.end();
        return false;
    }

    String payload = http.getString();
    http.end();

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
        Serial.printf("[Clima] Error JSON: %s\n", error.c_str());
        return false;
    }

    // Parsear clima actual
    outData.current.temperature = doc["current"]["temperature_2m"] | 0.0f;
    outData.current.humidity = doc["current"]["relative_humidity_2m"] | 0;
    outData.current.weatherCode = doc["current"]["weather_code"] | 0;
    outData.current.uvIndex = doc["current"]["uv_index"] | 0.0f;
    snprintf(outData.current.conditionText, sizeof(outData.current.conditionText), "%s",
             getWeatherDescription(outData.current.weatherCode));
    outData.current.iconType = getWeatherIconType(outData.current.weatherCode);

    // Parsear pronóstico de hoy
    const char* dateStr = doc["daily"]["time"][0] | "";
    snprintf(outData.today.date, sizeof(outData.today.date), "%s", dateStr);
    outData.today.tempMax = doc["daily"]["temperature_2m_max"][0] | 0.0f;
    outData.today.tempMin = doc["daily"]["temperature_2m_min"][0] | 0.0f;
    outData.today.weatherCode = doc["daily"]["weather_code"][0] | 0;
    outData.today.rainProbability = doc["daily"]["precipitation_probability_max"][0] | 0;
    outData.today.precipitation = doc["daily"]["precipitation_sum"][0] | 0.0f;
    outData.today.uvIndexMax = doc["daily"]["uv_index_max"][0] | 0.0f;
    snprintf(outData.today.conditionText, sizeof(outData.today.conditionText), "%s",
             getWeatherDescription(outData.today.weatherCode));
    outData.today.iconType = getWeatherIconType(outData.today.weatherCode);

    outData.valid = true;
    outData.lastFetchTime = millis();

    Serial.printf("[Clima] OK: Temp=%.1fC Hum=%d%% UV=%.1f | Max=%.1fC Min=%.1fC Lluvia=%.1fmm UVMax=%.1f\n",
                  outData.current.temperature, outData.current.humidity, outData.current.uvIndex,
                  outData.today.tempMax, outData.today.tempMin, outData.today.precipitation, outData.today.uvIndexMax);

    return true;
}
