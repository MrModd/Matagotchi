#include <cstdio>
#include <furi/core/log.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL 4
#endif

extern "C" {

void furi_log_print_format(FuriLogLevel level, const char* tag, const char* format, ...) {
	if(LOG_LEVEL < level) return;
	va_list args;
	printf(format, args);
}

}
