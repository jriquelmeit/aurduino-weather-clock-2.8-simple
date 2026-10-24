# Arduino Weather Clock 2.8" Simple

[![PlatformIO](https://img.shields.io/badge/PlatformIO-Core_6-orange?logo=platformio)](https://platformio.org/)
[![ESP8266](https://img.shields.io/badge/Board-NodeMCU_V2%2FV3_(ESP8266)-blue?logo=espressif)](https://www.espressif.com/)
[![Display](https://img.shields.io/badge/Display-ILI9341_SPI_2.8''-red)](https://www.adafruit.com/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?logo=arduino)](https://www.arduino.cc/)
[![Weather API](https://img.shields.io/badge/Weather_API-Open--Meteo-brightgreen)](https://open-meteo.com/)

Reloj digital de escritorio conectado a Internet para la placa **NodeMCU (ESP8266)** y pantalla gráfica **TFT SPI 2.8" (ILI9341)**.

Diseñado con un enfoque minimalista de **pantalla única**, priorizando el reloj en formato **`HH:MM` gigante centrado verticalmente**, acompañado en los laterales por el estado meteorológico actual y el pronóstico del día, y una cabecera con la fecha y el **Santo del Día** (santoral de los 366 días del año almacenado en memoria Flash PROGMEM).

---

## 🖥️ Diagrama ASCII del Display (320x240 px, Modo Horizontal)

```text
+-------------------------------------------------------------------------------+
|  24 de Octubre 2026 - S. Antonio M. Claret                             [||||] |
+-----------+-------------------------------------------------------+-----------+
|  ACTUAL   |                                                       |    HOY    |
|           |                        SABADO                         |           |
|    \ /    |  ---------------------------------------------------  |   \ | /   |
|   --O--   |                                                       |  --( O )  |
|    / \    |                                                       |   (____)  |
|  Despej.  |                     1 4 : 3 5                         |           |
|           |                                                       |    MAX    |
|   TEMP    |              (Reloj Gigante Centrado)                 |   16.2°   |
|   15.5°   |                                                       |           |
|           |  ---------------------------------------------------  |    MIN    |
|  HUMEDAD  |  [============ Barra de Segundos (0..59s) ==========] |    9.2°   |
|  💧 49%   |                                                       |           |
|           |                   Mayormente claro                    |  LLUVIA * |
| INDICE UV |                Hora sincronizada NTP                  |   5.6mm   |
|    3.5    |                                                       |   80%     |
|   Mod.    |                                                       | (o UV MAX)|
+-----------+-------------------------------------------------------+-----------+
| IP: 192.168.0.104 | Sincronizado NTP y Clima                      | Act: 14:30|
+-------------------------------------------------------------------------------+

* En el panel derecho ("HOY"):
  - Si la precipitación prevista es > 0.05 mm: Muestra los mm de lluvia acumulados y la probabilidad (%).
  - Si no llueve (0.0 mm): Muestra automáticamente el Índice UV Máximo previsto y su nivel de riesgo.
```

---

## ⚙️ Componentes y Hardware Utilizado

1. **Microcontrolador:** 
   - **Lolin / Amica NodeMCU V2 / V3** (módulo ESP8266 ESP-12E / ESP-12F).
   - CPU a 160 MHz, 80 KB RAM, 4 MB Flash.
   - Conectividad Wi-Fi 802.11 b/g/n (2.4 GHz).

2. **Pantalla:**
   - **TFT 2.8" SPI ILI9341**.
   - Resolución: 320x240 píxeles, 65K colores (RGB565).
   - Controlador: ILI9341 con interfaz SPI rápida (40 MHz).

---

## 🔌 Diagrama de Conexiones

### Tabla de Pines (NodeMCU ESP8266 ↔ Pantalla TFT ILI9341)

| Pin Pantalla TFT | Pin NodeMCU | GPIO ESP8266 | Descripción / Función |
| :--- | :--- | :--- | :--- |
| **VCC** | **VIN (5V)** ó **3V3** | - | Alimentación eléctrica |
| **GND** | **GND** | - | Tierra común |
| **CS** | **D8** | GPIO15 | Chip Select TFT (SPI) |
| **RESET / RST** | **D4** | GPIO2 | Reset del controlador TFT |
| **DC / RS** | **D3** | GPIO0 | Datos / Comando TFT |
| **SDI (MOSI)** | **D7** | GPIO13 | Bus HSPI - Datos hacia la pantalla |
| **SCK (CLK)** | **D5** | GPIO14 | Bus HSPI - Reloj SPI |
| **LED** | **3V3** ó pin **RX** | - ó GPIO3 | Retroiluminación (directo a 3V3 o transistor NPN en pin RX) |
| **SDO (MISO)** | *No conectar* | - | Desconectado para evitar conflictos SPI |

> **Nota sobre el pin LED de retroiluminación:** 
> - **Conexión simple:** Conectar directamente a **3V3**.
> - **Control por software:** Conectar a través de un transistor NPN (ej. 2N2222) controlado por el pin `RX` (GPIO3).

### Diagrama Esquemático ASCII

```text
                  DIAGRAMA DE CONEXIÓN
                 ======================

    LOLIN NODEMCU ESP8266                   PANTALLA TFT ILI9341 2.8" SPI
  +-----------------------+                 +---------------------------+
  |                       |                 |                           |
  |                   VIN +-----------------+ VCC (5V o 3V3)            |
  |                   GND +--------+--------+ GND                       |
  |                       |        |        |                           |
  |             D8 (GP15) +--------|--------+ CS                        |
  |             D4 (GP2)  +--------|--------+ RESET / RST               |
  |             D3 (GP0)  +--------|--------+ DC / RS                   |
  |             D7 (GP13) +--------|--------+ SDI (MOSI)                |
  |             D5 (GP14) +--------|--------+ SCK (CLK)                 |
  |                   3V3 +--------+--------+ LED (Retroiluminación)    |
  |                       |                 | SDO (MISO) [Desconectar]  |
  +-----------------------+                 +---------------------------+
```

---

## 🌟 Características Principales

- **Diseño de Pantalla Única:** Toda la información importante visible de un vistazo, sin necesidad de navegar entre menús ni páginas.
- **Reloj Gigante Centrado Verticalmente:** Números `HH:MM` en tamaño personalizado (`6x` de ancho por `7x` de alto, 56 px de altura) con color `GREENYELLOW` de alto contraste.
- **Día de la Semana Único:** El nombre del día (ej. `SÁBADO`) aparece solo una vez en la pantalla, en la parte superior del reloj central.
- **Santoral Católico Completo:** Cabecera con fecha y Santo del Día (`<día> de <mes> <año> - <santo>`), con los 366 días del año almacenados en memoria Flash (PROGMEM) sin consumir memoria RAM.
- **Costado Izquierdo (Estado Actual):**
  - Ícono del clima en tiempo real.
  - Temperatura actual en °C con símbolo de grado.
  - Humedad relativa con ícono de gota.
  - Índice UV actual junto con categoría y color dinámico (Bajo / Moderado / Alto / Muy Alto / Extremo).
- **Costado Derecho (Pronóstico de Hoy):**
  - Ícono de previsión diaria.
  - Temperaturas extremas (Máxima y Mínima).
  - Lógica automática: muestra milímetros de lluvia si se esperan precipitaciones (> 0.05 mm), o conmuta a Índice UV Máximo si el día es seco.
- **Barra de Segundos Fluida:** Indicador de avance de 0 a 59 segundos sin parpadeo.
- **Sin Parpadeo (*Flicker-Free*):** Redibujado selectivo por zonas: el reloj solo actualiza al cambiar el minuto y los datos meteorológicos cada 30 minutos.
- **Sincronización Horaria Automática (NTP + Regla POSIX):** Ajuste automático de horario de verano e invierno (Chile Continental).
- **API Gratuita Open-Meteo:** Sin necesidad de registrar API keys ni límites restrictivos.

---

## 🚀 Compilación y Carga con PlatformIO

### Requisitos
- [PlatformIO Core](https://platformio.org/) o extensión PlatformIO en VS Code / CLion.

### 1. Configuración (`config.h`)
Copia la plantilla `include/config.h.example` a `include/config.h` y edita tus credenciales Wi-Fi y ubicación:
```bash
cp include/config.h.example include/config.h
```
```cpp
#define WIFI_SSID       "Tu_Red_WiFi"
#define WIFI_PASSWORD   "Tu_Contraseña"
```

### 2. Compilar
```bash
pio run
```

### 3. Subir al Módulo ESP8266
Conecta el ESP8266 por USB y ejecuta:
```bash
pio run -t upload
```

### 4. Monitor Serie (Opcional)
```bash
pio device monitor -b 115200
```
