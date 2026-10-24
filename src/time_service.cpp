#include "time_service.h"
#include "santoral.h"
#include <coredecls.h>

static const char* SPANISH_DAYS[] = {
    "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"
};

static const char* SPANISH_SHORT_DAYS[] = {
    "Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"
};

static const char* SPANISH_MONTHS[] = {
    "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

void initTimeService(const char* tzRule, const char* server1, const char* server2) {
    configTime(tzRule, server1, server2);
}

bool isTimeSynchronized() {
    time_t now = time(nullptr);
    return (now > (time_t)1704067200LL); // Posterior a 2024
}

const char* getSpanishDayName(int wday) {
    if (wday >= 0 && wday < 7) {
        return SPANISH_DAYS[wday];
    }
    return "";
}

const char* getSpanishShortDayName(int wday) {
    if (wday >= 0 && wday < 7) {
        return SPANISH_SHORT_DAYS[wday];
    }
    return "";
}

const char* getSpanishMonthName(int month) {
    if (month >= 1 && month <= 12) {
        return SPANISH_MONTHS[month - 1];
    }
    return "";
}

bool getCurrentDateTime(DateTimeInfo& outInfo) {
    time_t now = time(nullptr);
    if (now < 100000) {
        return false;
    }

    struct tm timeinfo;
    localtime_r(&now, &timeinfo);

    outInfo.hour = timeinfo.tm_hour;
    outInfo.minute = timeinfo.tm_min;
    outInfo.second = timeinfo.tm_sec;
    outInfo.day = timeinfo.tm_mday;
    outInfo.month = timeinfo.tm_mon + 1;
    outInfo.year = timeinfo.tm_year + 1900;
    outInfo.dayOfWeek = timeinfo.tm_wday;
    outInfo.isDST = (timeinfo.tm_isdst > 0);

    snprintf(outInfo.timeStr, sizeof(outInfo.timeStr), "%02d:%02d:%02d",
             outInfo.hour, outInfo.minute, outInfo.second);

    snprintf(outInfo.shortTimeStr, sizeof(outInfo.shortTimeStr), "%02d:%02d",
             outInfo.hour, outInfo.minute);

    snprintf(outInfo.dayName, sizeof(outInfo.dayName), "%s",
             getSpanishDayName(outInfo.dayOfWeek));

    // Obtener Santo del Día
    char saintBuf[36];
    getSaintOfTheDay(outInfo.day, outInfo.month, saintBuf, sizeof(saintBuf));

    if (saintBuf[0] != '\0') {
        snprintf(outInfo.dateStr, sizeof(outInfo.dateStr), "%d de %s %d - %s",
                 outInfo.day,
                 getSpanishMonthName(outInfo.month),
                 outInfo.year,
                 saintBuf);
    } else {
        snprintf(outInfo.dateStr, sizeof(outInfo.dateStr), "%d de %s %d",
                 outInfo.day,
                 getSpanishMonthName(outInfo.month),
                 outInfo.year);
    }

    return true;
}
