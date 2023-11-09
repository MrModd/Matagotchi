#include "game/constants.h"
#include "game/game_structs.h"
#include "game/save_restore.h"
#include <cstdio>
#include <gtest/gtest.h>

bool operator==(const PersistentGameState &a, const PersistentGameState &b) {
  return a.xp == b.xp &&
		a.stage == b.stage &&
		a.last_recorded_xp_update == b.last_recorded_xp_update;
}

class TestSaveRestore : public ::testing::Test {
public:
  TestSaveRestore() {
		clean();
	}
  virtual ~TestSaveRestore() {
		clean();
	}

private:
  void clean() {
		std::remove(GAME_STATE_STORAGE_PATH);
	}
};

TEST_F(TestSaveRestore, save_to_file) {
  PersistentGameState initialState;
	initialState.xp = 100;
	initialState.stage = LifeStage::CHILD;
	initialState.last_recorded_xp_update = 3;

  PersistentGameState loadedState;

  ASSERT_TRUE(save_to_file(&initialState));
  ASSERT_TRUE(load_from_file(&loadedState));

  EXPECT_EQ(initialState, loadedState);
}
