#include "CloudPLCRTC.h"

CloudPLCRTC::CloudPLCRTC() {}

void CloudPLCRTC::begin() {
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1) delay(10);
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting the time!");
        adjustToCompileTime();
    }
}

void CloudPLCRTC::adjustToCompileTime() {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void CloudPLCRTC::adjustToDateTime(int year, int month, int day, int hour, int minute, int second) {
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

String CloudPLCRTC::getFormattedTime() {
    DateTime now = rtc.now();
    char buf[9];
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    return String(buf);
}

String CloudPLCRTC::getFormattedDate() {
    DateTime now = rtc.now();
    char buf[11];
    snprintf(buf, sizeof(buf), "%04d/%02d/%02d", now.year(), now.month(), now.day());
    return String(buf);
}

String CloudPLCRTC::getFormattedDateTime() {
    DateTime now = rtc.now();
    char buf[30];  // Increased buffer size to ensure it fits the formatted string
    snprintf(buf, sizeof(buf), "%04d/%02d/%02d %02d:%02d:%02d (%s)", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second(), daysOfTheWeek[now.dayOfTheWeek()]);
    return String(buf);
}

uint32_t CloudPLCRTC::getUnixTime() {
    return rtc.now().unixtime();
}

String CloudPLCRTC::getFutureTime(int days, int hours, int minutes, int seconds) {
    DateTime now = rtc.now();
    DateTime future(now + TimeSpan(days, hours, minutes, seconds));
    char buf[20];
    snprintf(buf, sizeof(buf), "%04d/%02d/%02d %02d:%02d:%02d", future.year(), future.month(), future.day(), future.hour(), future.minute(), future.second());
    return String(buf);
}
