#include <gtest/gtest.h>
#include <src/game/constants.h>
#include <src/game/game_structs.h>
#include <src/game/save_restore.h>
#include <storage/storage.h>

bool operator==(const PersistentGameState &a, const PersistentGameState &b) {
  return a == b;
}

class TestSaveRestore : public ::testing::Test {
public:
  TestSaveRestore() {
    Storage *storage = static_cast<Storage *>(furi_record_open(RECORD_STORAGE));

    storage_simply_remove(storage, GAME_STATE_STORAGE_PATH);

    furi_record_close(RECORD_STORAGE);
  }
};

TEST_F(TestSaveRestore, restore_saved_results_in_same_obj) {
  PersistentGameState initial;
  PersistentGameState loaded;

  ASSERT_TRUE(save_to_file(&initial));
  ASSERT_TRUE(load_from_file(&loaded));

  EXPECT_EQ(initial, loaded);
}
