#ifndef CLOUDPLCRTC_H
#define CLOUDPLCRTC_H

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

class CloudPLCRTC {
public:
    CloudPLCRTC();

    void begin();
    void adjustToCompileTime();
    void adjustToDateTime(int year, int month, int day, int hour, int minute, int second);
    String getFormattedTime();
    String getFormattedDate();
    String getFormattedDateTime();
    uint32_t getUnixTime();
    String getFutureTime(int days, int hours, int minutes, int seconds);

private:
    RTC_DS3231 rtc;
    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
};

#endif
