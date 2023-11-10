#include <cstdlib>
#include <furi_hal.h>

#ifndef SRAND_SEED
#define SRAND_SEED 1
#endif

uint32_t furi_hal_random_get() {
	std::srand(SRAND_SEED);
  return std::rand();
}
