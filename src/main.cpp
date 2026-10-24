#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "time_service.h"
#include "weather_service.h"
#include "display_ui.h"

static DisplayUI ui(TFT_CS, TFT_DC, TFT_RST, TFT_LED_PIN);
static WeatherService weatherService;
static WeatherData weatherData;

static unsigned long lastClockTick = 0;
static unsigned long lastWeatherAttempt = 0;
static unsigned long lastWifiCheck = 0;
static bool initialWeatherFetched = false;

void connectWiFi() {
    Serial.println(F("\n========================================"));
    Serial.printf("Conectando a Wi-Fi: %s\n", WIFI_SSID);
    Serial.println(F("========================================"));

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint8_t dots = 0;
    unsigned long startAttempt = millis();

    while (WiFi.status() != WL_CONNECTED && (millis() - startAttempt < 20000)) {
        delay(100);
        Serial.print(F("."));
        if ((dots % 4) == 0) {
            ui.updateBootProgress("Conectando Wi-Fi", dots / 4);
        }
        dots++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println(F("\n[Wi-Fi] Conectado exitosamente!"));
        Serial.printf("  IP: %s | RSSI: %d dBm\n", WiFi.localIP().toString().c_str(), WiFi.RSSI());
        ui.updateBootProgress("Wi-Fi OK, esperando hora", 4);
    } else {
        Serial.println(F("\n[Wi-Fi] Advertencia: Tiempo de espera agotado"));
        ui.updateBootProgress("Fallo conexion Wi-Fi", 0);
    }
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println(F("\n[Inicio] Reloj Meteorologico Simple 2.8\""));

    // Inicializar Pantalla
    ui.begin(TFT_ROTATION);
    ui.showBootScreen(WIFI_SSID);

    // Conectar a Wi-Fi
    connectWiFi();

    // Iniciar servicio horario NTP
    Serial.println(F("[NTP] Iniciando sincronizacion horaria..."));
    initTimeService(TIMEZONE_RULE, NTP_SERVER_1, NTP_SERVER_2);

    // Esperar sincronización de hora inicial (máx 10 segundos)
    unsigned long startNtp = millis();
    while (!isTimeSynchronized() && (millis() - startNtp < 10000)) {
        delay(200);
        Serial.print(F("t"));
    }
    Serial.println();

    // Dibujar diseño base de la pantalla única
    ui.drawBaseLayout();

    // Primera sincronización visual de hora
    DateTimeInfo dt;
    if (getCurrentDateTime(dt)) {
        ui.updateDate(dt);
        ui.updateTime(dt);
    }

    // Primera consulta del clima
    if (WiFi.status() == WL_CONNECTED) {
        ui.updateStatusBar("Consultando datos de clima...");
        if (weatherService.fetchWeather(LOCATION_LAT, LOCATION_LON, weatherData)) {
            ui.updateWeather(weatherData);
            initialWeatherFetched = true;
            lastWeatherAttempt = millis();
            char statusMsg[40];
            snprintf(statusMsg, sizeof(statusMsg), "IP: %s | Sincronizado", WiFi.localIP().toString().c_str());
            ui.updateStatusBar(statusMsg);
        } else {
            ui.updateStatusBar("Error al obtener clima inicial");
            lastWeatherAttempt = millis() - WEATHER_REFRESH_INTERVAL_MS + WEATHER_RETRY_INTERVAL_MS;
        }
    } else {
        ui.updateStatusBar("Sin conexion Wi-Fi");
    }

    ui.updateWifiStatus(WiFi.status() == WL_CONNECTED, WiFi.RSSI(), WiFi.localIP());
}

void loop() {
    unsigned long now = millis();

    // 1. Refresco del reloj cada 1000 ms (o cambio de segundo)
    if (now - lastClockTick >= CLOCK_REFRESH_INTERVAL_MS) {
        lastClockTick = now;

        DateTimeInfo dt;
        if (getCurrentDateTime(dt)) {
            ui.updateTime(dt);
            ui.updateDate(dt);
        }
    }

    // 2. Consulta y refresco meteorológico periódico
    unsigned long weatherInterval = initialWeatherFetched ? WEATHER_REFRESH_INTERVAL_MS : WEATHER_RETRY_INTERVAL_MS;
    if (now - lastWeatherAttempt >= weatherInterval) {
        lastWeatherAttempt = now;

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println(F("[Loop] Actualizando datos meteorologicos..."));
            if (weatherService.fetchWeather(LOCATION_LAT, LOCATION_LON, weatherData)) {
                ui.updateWeather(weatherData);
                initialWeatherFetched = true;

                DateTimeInfo dt;
                char statusMsg[45];
                if (getCurrentDateTime(dt)) {
                    snprintf(statusMsg, sizeof(statusMsg), "IP: %s | Act: %02d:%02d",
                             WiFi.localIP().toString().c_str(), dt.hour, dt.minute);
                } else {
                    snprintf(statusMsg, sizeof(statusMsg), "IP: %s | Clima OK", WiFi.localIP().toString().c_str());
                }
                ui.updateStatusBar(statusMsg);
            } else {
                Serial.println(F("[Loop] Error al actualizar clima, reintentando en 1 min"));
                ui.updateStatusBar("Error actualizando clima");
                // Reintentar más rápido en caso de fallo
                lastWeatherAttempt = now - weatherInterval + WEATHER_RETRY_INTERVAL_MS;
            }
        } else {
            Serial.println(F("[Loop] Wi-Fi desconectado, intentando reconectar..."));
            WiFi.reconnect();
        }
    }

    // 3. Verificación periódica del estado de la señal Wi-Fi (cada 5 segundos)
    if (now - lastWifiCheck >= 5000UL) {
        lastWifiCheck = now;
        ui.updateWifiStatus(WiFi.status() == WL_CONNECTED, WiFi.RSSI(), WiFi.localIP());
    }

    yield(); // Mantener alimentado el Watchdog del ESP8266
}
