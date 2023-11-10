BUILD_DIR := build

GTEST_DIR := lib/googletest/googletest
GTEST_CPP_FLAGS := -I$(GTEST_DIR) -I$(GTEST_DIR)/include -pthread
GTEST_LIB := $(BUILD_DIR)/libgtest.a

TESTS := $(shell find test/game -type f -name '*.cpp')
TEST_STUBS := $(shell find test/stubs -type f -name '*.c*')
TEST_MOCKS := $(shell find test/mocks -type f -name '*.c*')
MOCKED_GAME_SRC := src/game/random_generator.c

GAME_SRC := $(shell find src/game -type f -name '*.c*')

TEST_GAME_SRC := $(filter-out $(MOCKED_GAME_SRC), $(GAME_SRC))

GAME_CPP_FLAGS := -Isrc
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/applications/services
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/furi
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/mlib
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/ST25RFAL002
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/ST25RFAL002/include
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/ST25RFAL002/source/st25r3916
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/libusb_stm32/inc
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/cmsis_core
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/FreeRTOS-Kernel/include
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/stm32wb_hal/Inc
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/lib/stm32wb_cmsis/Include
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/firmware/targets/furi_hal_include
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/firmware/targets/f7/furi_hal
GAME_CPP_FLAGS += -I/home/stefano/.ufbt/current/sdk_headers/f7_sdk/firmware/targets/f7/ble_glue
GAME_CPP_FLAGS += -DSTM32WB -DSTM32WB55xx -DUSE_FULL_LL_DRIVER -D"_Static_assert(x,y)=" -D"_ATTRIBUTE=__attribute__"

TEST_CPP_FLAGS := -Itest/stubs -Itest -DLOG_LEVEL=0
TEST_CPP_FLAGS += -Wno-overflow -Wno-int-to-pointer-cast -fpermissive

$(GTEST_LIB): $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) -c $(GTEST_CPP_FLAGS) -o $(BUILD_DIR)/gtest-all.o $^
	ar -rcs $@ $(BUILD_DIR)/gtest-all.o

# our source files must go before the library file, see https://stackoverflow.com/a/40603678/4046810
test: $(TESTS) $(GTEST_DIR)/src/gtest_main.cc $(GTEST_LIB) $(TEST_STUBS) $(TEST_MOCKS) $(TEST_GAME_SRC)
	$(CXX) $(GTEST_CPP_FLAGS) $(TEST_CPP_FLAGS) $(GAME_CPP_FLAGS) -o $(BUILD_DIR)/test $^ -Lbuild -lgtest

debug: GTEST_CPP_FLAGS += -g3
debug: TEST_CPP_FLAGS += -g3
debug: test

.PHONY clean:
	rm -rf $(BUILD_DIR)/*
