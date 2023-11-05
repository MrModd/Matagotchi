#include <furi/core/core_defines.h>
#include <furi_hal_random.h>
#include <gtest/gtest.h>

extern "C" int32_t test_matagotchi_app(void *p) {
  UNUSED(p);

  /* Perform required RTOS init sequences */
  furi_hal_random_init();

  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
