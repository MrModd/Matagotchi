#include <furi/core/check.h>

extern "C" {

FURI_NORETURN void __furi_crash() {
	throw "__furi_crash";
}

}
