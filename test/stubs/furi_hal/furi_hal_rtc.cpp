#include <ctime>
#include <furi_hal_rtc.h>

extern "C" {

void furi_hal_rtc_get_datetime(FuriHalRtcDateTime* datetime) {
    time_t     now = time(0);
		std::tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

		datetime->minute = tstruct.tm_min;
		datetime->hour = tstruct.tm_hour;
		datetime->second = tstruct.tm_sec;

		datetime->weekday = tstruct.tm_wday;

		datetime->day = tstruct.tm_mday;
		datetime->month = tstruct.tm_mon;
		datetime->year = tstruct.tm_year;
}

uint32_t furi_hal_rtc_datetime_to_timestamp(FuriHalRtcDateTime* datetime) {
	std::tm tstruct;

	tstruct.tm_min = datetime->minute;
	tstruct.tm_hour = datetime->hour;
	tstruct.tm_sec = datetime->second;

	tstruct.tm_wday = datetime->weekday;

	tstruct.tm_mday = datetime->day;
	tstruct.tm_mon = datetime->month;
	tstruct.tm_year = datetime->year;

	return std::mktime(&tstruct);
}

}
