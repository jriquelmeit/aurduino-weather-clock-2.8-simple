#include "display_ui.h"

#define COLOR_BG_HEADER       0x0926
#define COLOR_BORDER_CARD     0x2145
#define COLOR_TEXT_MUTED      0x8410

DisplayUI::DisplayUI(uint8_t cs, uint8_t dc, uint8_t rst, int8_t ledPin)
    : _tft(cs, dc, rst),
      _ledPin(ledPin),
      _lastSecond(-1),
      _lastRssi(-999),
      _lastWifiState(false) {
    _lastTimeStr[0] = '\0';
    _lastDateStr[0] = '\0';
    _lastDayName[0] = '\0';
}

void DisplayUI::begin(uint8_t rotation) {
    if (_ledPin >= 0) {
        pinMode(_ledPin, OUTPUT);
        digitalWrite(_ledPin, HIGH); // Encender backlight
    }
    _tft.begin(40000000); // 40 MHz SPI
    _tft.setRotation(rotation);
    _tft.fillScreen(ILI9341_BLACK);
}

void DisplayUI::showBootScreen(const char* ssid) {
    _tft.fillScreen(ILI9341_BLACK);

    // Cabecera inicial
    _tft.fillRect(0, 0, 320, 36, COLOR_BG_HEADER);
    _tft.drawFastHLine(0, 36, 320, ILI9341_CYAN);

    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_WHITE);
    _tft.setCursor(14, 10);
    _tft.print("Reloj y Clima ESP8266");

    // Recuadro central
    _tft.drawRoundRect(15, 55, 290, 155, 8, ILI9341_DARKGREY);

    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_YELLOW);
    _tft.setCursor(30, 72);
    _tft.print("Iniciando Sistema");

    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_LIGHTGREY);
    _tft.setCursor(30, 110);
    _tft.print("Conectando a Wi-Fi:");

    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_CYAN);
    _tft.setCursor(30, 126);
    _tft.print(ssid);

    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_GREENYELLOW);
    _tft.setCursor(30, 160);
    _tft.print("Sincronizando hora NTP y clima...");
}

void DisplayUI::updateBootProgress(const char* stepMsg, uint8_t dots) {
    _tft.fillRect(30, 180, 260, 20, ILI9341_BLACK);
    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_ORANGE);
    _tft.setCursor(30, 185);
    _tft.print(stepMsg);

    for (uint8_t i = 0; i < (dots % 5); i++) {
        _tft.print(".");
    }
}

void DisplayUI::drawBaseLayout() {
    _tft.fillScreen(ILI9341_BLACK);

    // 1. Barra de Cabecera (Y: 0..24) - Sin ubicación fija, dedicada a la fecha
    _tft.fillRect(0, 0, 320, 24, COLOR_BG_HEADER);
    _tft.drawFastHLine(0, 24, 320, ILI9341_CYAN);

    // 2. Tarjeta Izquierda: Estado Actual (X: 3..67, Y: 26..222)
    _tft.drawRoundRect(3, 26, 64, 196, 5, COLOR_BORDER_CARD);
    _tft.drawFastHLine(6, 42, 58, COLOR_BORDER_CARD);
    _tft.drawFastHLine(6, 90, 58, COLOR_BORDER_CARD);
    _tft.drawFastHLine(6, 130, 58, COLOR_BORDER_CARD);
    _tft.drawFastHLine(6, 170, 58, COLOR_BORDER_CARD);

    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    _tft.setCursor(16, 31);
    _tft.print("ACTUAL");

    _tft.setTextColor(COLOR_TEXT_MUTED, ILI9341_BLACK);
    _tft.setCursor(8, 94);
    _tft.print("TEMP");

    _tft.setCursor(8, 134);
    _tft.print("HUMEDAD");

    _tft.setCursor(6, 174);
    _tft.print("INDICE UV");

    // 3. Tarjeta Central: Reloj Principal (X: 70..250, Y: 26..222, Ancho: 180)
    _tft.drawRoundRect(70, 26, 180, 196, 5, COLOR_BORDER_CARD);
    _tft.drawFastHLine(76, 68, 168, COLOR_BORDER_CARD);  // Divisor superior
    _tft.drawFastHLine(76, 160, 168, COLOR_BORDER_CARD); // Divisor inferior

    // Marco barra de segundos (X: 86, Y: 168, Ancho: 148, Alto: 6)
    _tft.drawRect(86, 168, 148, 6, COLOR_BORDER_CARD);

    // 4. Tarjeta Derecha: Pronóstico Hoy (X: 253..317, Y: 26..222)
    _tft.drawRoundRect(253, 26, 64, 196, 5, COLOR_BORDER_CARD);
    _tft.drawFastHLine(256, 42, 58, COLOR_BORDER_CARD);
    _tft.drawFastHLine(256, 82, 58, COLOR_BORDER_CARD);
    _tft.drawFastHLine(256, 144, 58, COLOR_BORDER_CARD);

    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    _tft.setCursor(276, 31);
    _tft.print("HOY");

    _tft.setTextColor(COLOR_TEXT_MUTED, ILI9341_BLACK);
    _tft.setCursor(257, 86);
    _tft.print("MAX");

    _tft.setCursor(257, 116);
    _tft.print("MIN");

    // 5. Barra inferior (Y: 224..240)
    _tft.drawFastHLine(0, 224, 320, COLOR_BORDER_CARD);

    // Reset de caché
    _lastTimeStr[0] = '\0';
    _lastDateStr[0] = '\0';
    _lastDayName[0] = '\0';
    _lastSecond = -1;
    _lastRssi = -999;
    _lastWifiState = false;
}

void DisplayUI::updateTime(const DateTimeInfo& timeInfo) {
    // 1. Día de la semana (Centrado arriba del reloj, Y: 38..54)
    if (strncmp(_lastDayName, timeInfo.dayName, sizeof(_lastDayName)) != 0) {
        _tft.fillRect(72, 32, 176, 32, ILI9341_BLACK);
        _tft.setTextSize(2);
        _tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
        int len = strlen(timeInfo.dayName);
        int x = 70 + (180 - (len * 12)) / 2;
        _tft.setCursor(x > 72 ? x : 72, 42);
        _tft.print(timeInfo.dayName);
        strncpy(_lastDayName, timeInfo.dayName, sizeof(_lastDayName));
    }

    // 2. Reloj en formato HH:MM (Tamaño aumentado: 6x horizontal, 7x vertical)
    // Centrado exactamente vertical (Y: 94..150, Altura 56 px sobre área central de Y: 24..224)
    if (strncmp(_lastTimeStr, timeInfo.shortTimeStr, sizeof(_lastTimeStr)) != 0) {
        _tft.fillRect(72, 90, 176, 62, ILI9341_BLACK);
        _tft.setTextSize(6, 7);
        _tft.setTextColor(ILI9341_GREENYELLOW, ILI9341_BLACK);
        _tft.setCursor(73, 94);
        _tft.print(timeInfo.shortTimeStr);
        strncpy(_lastTimeStr, timeInfo.shortTimeStr, sizeof(_lastTimeStr));
    }

    // 3. Barra de segundos fluida (X: 88, Y: 170, Ancho: 144)
    if (timeInfo.second != _lastSecond) {
        int barW = 144;
        int fillW = (timeInfo.second * barW) / 59;
        if (timeInfo.second == 0) {
            _tft.fillRect(88, 170, barW, 2, ILI9341_BLACK);
        }
        if (fillW > 0) {
            _tft.fillRect(88, 170, fillW, 2, ILI9341_CYAN);
        }
        _lastSecond = timeInfo.second;
    }
}

void DisplayUI::updateDate(const DateTimeInfo& timeInfo) {
    if (strncmp(_lastDateStr, timeInfo.dateStr, sizeof(_lastDateStr)) != 0) {
        _tft.fillRect(6, 4, 290, 16, COLOR_BG_HEADER);
        _tft.setTextSize(1);
        _tft.setTextColor(ILI9341_WHITE, COLOR_BG_HEADER);
        _tft.setCursor(8, 8);
        _tft.print(timeInfo.dateStr);
        strncpy(_lastDateStr, timeInfo.dateStr, sizeof(_lastDateStr));
    }
}

void DisplayUI::updateWeather(const WeatherData& weather) {
    if (!weather.valid) return;

    // ==========================================
    // 1. COSTADO IZQUIERDO: ESTADO ACTUAL
    // ==========================================
    // Limpiar icono y condición
    _tft.fillRect(5, 44, 60, 44, ILI9341_BLACK);
    drawWeatherIcon(35, 58, weather.current.iconType, false);

    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    char shortCond[11];
    if (strlen(weather.current.conditionText) > 9) {
        strncpy(shortCond, weather.current.conditionText, 9);
        shortCond[9] = '\0';
    } else {
        strncpy(shortCond, weather.current.conditionText, sizeof(shortCond));
    }
    int condX = 3 + (64 - (strlen(shortCond) * 6)) / 2;
    _tft.setCursor(condX > 5 ? condX : 5, 78);
    _tft.print(shortCond);

    // Temperatura actual (formato "15.5°")
    _tft.fillRect(5, 105, 60, 22, ILI9341_BLACK);
    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_ORANGE, ILI9341_BLACK);
    _tft.setCursor(8, 107);
    _tft.printf("%.1f", weather.current.temperature);
    _tft.drawCircle(58, 107, 2, ILI9341_ORANGE);

    // Humedad actual
    _tft.fillRect(5, 144, 60, 22, ILI9341_BLACK);
    drawWaterDrop(8, 151, ILI9341_CYAN);
    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    _tft.setCursor(18, 147);
    _tft.printf("%d%%", weather.current.humidity);

    // Índice UV actual
    _tft.fillRect(5, 184, 60, 34, ILI9341_BLACK);
    uint16_t uvCol = getUvColor(weather.current.uvIndex);
    _tft.setTextSize(2);
    _tft.setTextColor(uvCol, ILI9341_BLACK);
    _tft.setCursor(8, 185);
    _tft.printf("%.1f", weather.current.uvIndex);

    _tft.setTextSize(1);
    _tft.setTextColor(uvCol, ILI9341_BLACK);
    _tft.setCursor(8, 204);
    _tft.print(getUvCategory(weather.current.uvIndex));

    // ==========================================
    // 2. PANEL CENTRAL: DETALLE INFERIOR (SIN UBICACIÓN)
    // ==========================================
    _tft.fillRect(72, 180, 176, 38, ILI9341_BLACK);
    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    int fullCondLen = strlen(weather.current.conditionText);
    int fullCondX = 70 + (180 - (fullCondLen * 6)) / 2;
    _tft.setCursor(fullCondX > 72 ? fullCondX : 72, 184);
    _tft.print(weather.current.conditionText);

    _tft.setTextColor(COLOR_TEXT_MUTED, ILI9341_BLACK);
    const char* ntpMsg = "Hora sincronizada NTP";
    int ntpX = 70 + (180 - (strlen(ntpMsg) * 6)) / 2;
    _tft.setCursor(ntpX, 200);
    _tft.print(ntpMsg);

    // ==========================================
    // 3. COSTADO DERECHO: PRONÓSTICO HOY
    // ==========================================
    // Limpiar icono de hoy
    _tft.fillRect(255, 44, 60, 36, ILI9341_BLACK);
    drawWeatherIcon(285, 58, weather.today.iconType, false);

    // Temp Máxima
    _tft.fillRect(255, 96, 60, 18, ILI9341_BLACK);
    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_ORANGE, ILI9341_BLACK);
    _tft.setCursor(257, 97);
    _tft.printf("%.1f", weather.today.tempMax);
    _tft.drawCircle(308, 97, 2, ILI9341_ORANGE);

    // Temp Mínima
    _tft.fillRect(255, 125, 60, 18, ILI9341_BLACK);
    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    _tft.setCursor(257, 126);
    _tft.printf("%.1f", weather.today.tempMin);
    _tft.drawCircle(308, 126, 2, ILI9341_CYAN);

    // Condicional: Lluvia vs Índice UV Máximo de Hoy
    _tft.fillRect(255, 148, 60, 68, ILI9341_BLACK);
    if (weather.today.precipitation > 0.05f) {
        // Mostrar lluvia en mm y probabilidad
        _tft.setTextSize(1);
        _tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        _tft.setCursor(257, 150);
        _tft.print("LLUVIA");

        _tft.setTextSize(2);
        _tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
        _tft.setCursor(257, 164);
        _tft.printf("%.1f", weather.today.precipitation);

        _tft.setTextSize(1);
        _tft.setCursor(296, 170);
        _tft.print("mm");

        _tft.setTextColor(ILI9341_LIGHTGREY, ILI9341_BLACK);
        _tft.setCursor(257, 192);
        _tft.printf("%d%%", weather.today.rainProbability);
    } else {
        // Mostrar UV Máximo previsto para hoy
        uint16_t uvMaxCol = getUvColor(weather.today.uvIndexMax);
        _tft.setTextSize(1);
        _tft.setTextColor(COLOR_TEXT_MUTED, ILI9341_BLACK);
        _tft.setCursor(257, 150);
        _tft.print("UV MAX");

        _tft.setTextSize(2);
        _tft.setTextColor(uvMaxCol, ILI9341_BLACK);
        _tft.setCursor(257, 164);
        _tft.printf("%.1f", weather.today.uvIndexMax);

        _tft.setTextSize(1);
        _tft.setTextColor(uvMaxCol, ILI9341_BLACK);
        _tft.setCursor(257, 192);
        _tft.print(getUvCategory(weather.today.uvIndexMax));
    }
}

void DisplayUI::drawWaterDrop(int x, int y, uint16_t color) {
    _tft.drawPixel(x, y, color);
    _tft.drawFastHLine(x - 1, y + 1, 3, color);
    _tft.drawFastHLine(x - 2, y + 2, 5, color);
    _tft.fillRect(x - 2, y + 3, 5, 3, color);
    _tft.drawFastHLine(x - 1, y + 6, 3, color);
}

void DisplayUI::drawWifiIndicator(int x, int y, bool connected, int rssi) {
    _tft.fillRect(x, y, 16, 14, COLOR_BG_HEADER);

    if (!connected) {
        _tft.drawLine(x + 2, y + 2, x + 12, y + 12, ILI9341_RED);
        _tft.drawLine(x + 12, y + 2, x + 2, y + 12, ILI9341_RED);
        return;
    }

    uint16_t barColor = ILI9341_GREEN;
    if (rssi < -80) barColor = ILI9341_RED;
    else if (rssi < -70) barColor = ILI9341_YELLOW;

    int bars = 1;
    if (rssi >= -60) bars = 4;
    else if (rssi >= -70) bars = 3;
    else if (rssi >= -80) bars = 2;

    for (int b = 0; b < 4; b++) {
        int barH = (b + 1) * 3;
        uint16_t c = (b < bars) ? barColor : ILI9341_DARKGREY;
        _tft.fillRect(x + (b * 4), y + (12 - barH), 2, barH, c);
    }
}

void DisplayUI::updateWifiStatus(bool connected, int rssi, const IPAddress& ip) {
    if (connected != _lastWifiState || abs(rssi - _lastRssi) > 4) {
        drawWifiIndicator(298, 5, connected, rssi);
        _lastWifiState = connected;
        _lastRssi = rssi;
    }
}

void DisplayUI::updateStatusBar(const char* message) {
    _tft.fillRect(0, 226, 320, 14, ILI9341_BLACK);
    _tft.setTextSize(1);
    _tft.setTextColor(COLOR_TEXT_MUTED, ILI9341_BLACK);
    _tft.setCursor(6, 228);
    _tft.print(message);
}

void DisplayUI::drawWeatherIcon(int x, int y, WeatherIconType type, bool small) {
    int r = small ? 5 : 8;

    switch (type) {
        case ICON_SUNNY:
            _tft.fillCircle(x, y, r, ILI9341_YELLOW);
            for (int i = 0; i < 8; i++) {
                float angle = i * (3.14159f / 4.0f);
                int x1 = x + (int)((r + 2) * cos(angle));
                int y1 = y + (int)((r + 2) * sin(angle));
                int x2 = x + (int)((r + 4) * cos(angle));
                int y2 = y + (int)((r + 4) * sin(angle));
                _tft.drawLine(x1, y1, x2, y2, ILI9341_ORANGE);
            }
            break;

        case ICON_PARTLY_CLOUDY:
            _tft.fillCircle(x - (small ? 4 : 5), y - (small ? 4 : 5), small ? 4 : 5, ILI9341_YELLOW);
            _tft.fillCircle(x, y + 2, small ? 4 : 5, ILI9341_WHITE);
            _tft.fillCircle(x + (small ? 5 : 6), y + 3, small ? 3 : 4, ILI9341_LIGHTGREY);
            _tft.fillRect(x - (small ? 4 : 5), y + (small ? 3 : 4), small ? 11 : 14, small ? 4 : 5, ILI9341_WHITE);
            break;

        case ICON_CLOUDY:
            _tft.fillCircle(x - (small ? 4 : 5), y + 1, small ? 4 : 5, ILI9341_LIGHTGREY);
            _tft.fillCircle(x + 1, y - (small ? 3 : 4), small ? 5 : 6, ILI9341_WHITE);
            _tft.fillCircle(x + (small ? 5 : 6), y + 2, small ? 4 : 5, ILI9341_LIGHTGREY);
            _tft.fillRect(x - (small ? 4 : 5), y + (small ? 2 : 3), small ? 12 : 15, small ? 4 : 5, ILI9341_WHITE);
            break;

        case ICON_RAIN:
            _tft.fillCircle(x - 4, y - 2, 4, ILI9341_LIGHTGREY);
            _tft.fillCircle(x + 1, y - 4, 5, ILI9341_DARKGREY);
            _tft.fillCircle(x + 5, y - 1, 4, ILI9341_LIGHTGREY);
            _tft.fillRect(x - 4, y - 1, 12, 4, ILI9341_LIGHTGREY);
            _tft.drawLine(x - 3, y + 5, x - 5, y + 8, ILI9341_CYAN);
            _tft.drawLine(x + 1, y + 5, x - 1, y + 8, ILI9341_CYAN);
            _tft.drawLine(x + 5, y + 5, x + 3, y + 8, ILI9341_CYAN);
            break;

        case ICON_SNOW:
            _tft.fillCircle(x - 4, y - 2, 4, ILI9341_LIGHTGREY);
            _tft.fillCircle(x + 1, y - 4, 5, ILI9341_WHITE);
            _tft.fillCircle(x + 5, y - 1, 4, ILI9341_LIGHTGREY);
            _tft.fillRect(x - 4, y - 1, 12, 4, ILI9341_LIGHTGREY);
            _tft.drawPixel(x - 3, y + 6, ILI9341_WHITE);
            _tft.drawPixel(x + 1, y + 7, ILI9341_WHITE);
            _tft.drawPixel(x + 5, y + 6, ILI9341_WHITE);
            break;

        case ICON_THUNDERSTORM:
            _tft.fillCircle(x - 4, y - 2, 4, 0x4208);
            _tft.fillCircle(x + 1, y - 5, 5, 0x2104);
            _tft.fillCircle(x + 5, y - 1, 4, 0x4208);
            _tft.fillRect(x - 4, y - 1, 12, 4, 0x4208);
            _tft.drawLine(x + 1, y + 3, x - 1, y + 7, ILI9341_YELLOW);
            _tft.drawLine(x - 1, y + 7, x + 1, y + 7, ILI9341_YELLOW);
            _tft.drawLine(x + 1, y + 7, x - 2, y + 10, ILI9341_YELLOW);
            break;

        default:
            _tft.fillCircle(x, y, r, ILI9341_DARKGREY);
            break;
    }
}
