#include <gtest/gtest.h>
#include "game/constants.h"
#include "game/feature_management.h"
#include "game/game_structs.h"
#include "mocks/game/random_controller.h"

extern RandomController random_controller;

class TestXpManagement: public ::testing::Test {
	protected:
		GameState game_state;

	public:
		TestXpManagement() {
			game_state.persistent.last_recorded_xp_update = 0;
			game_state.persistent.xp = 0;
			game_state.persistent.stage = LifeStage::CHILD;
		}
};

TEST_F(TestXpManagement, apply_xp__no_xp_to_apply_still_updates_timestamp) {
	GameEvents events;
	events.xp = 0;
	events.xp_timestamp = 1;

	EXPECT_FALSE(apply_xp(&game_state, events));
	EXPECT_EQ(1, game_state.persistent.last_recorded_xp_update);
}

TEST_F(TestXpManagement, apply_xp__some_xp_but_dead_only_update_timestamp) {
	GameEvents events;
	events.xp = 0;
	events.xp_timestamp = 1;

	game_state.persistent.stage = LifeStage::DEAD;

	EXPECT_FALSE(apply_xp(&game_state, events));
	EXPECT_EQ(1, game_state.persistent.last_recorded_xp_update);
}

TEST_F(TestXpManagement, apply_xp__valid_xp_for_current_stage) {
	GameEvents events;
	events.xp = 2;
	events.xp_timestamp = 1;

	EXPECT_TRUE(apply_xp(&game_state, events));
	EXPECT_EQ(1, game_state.persistent.last_recorded_xp_update);
	EXPECT_EQ(2, game_state.persistent.xp);
	EXPECT_EQ(LifeStage::CHILD, game_state.persistent.stage);
}

TEST_F(TestXpManagement, apply_xp__too_many_xp_for_current_stage_transfer_to_next_stage) {
	game_state.persistent.stage = LifeStage::BABY;

	GameEvents events;
	events.xp = MAX_XP_PER_STAGE[LifeStage::BABY] + 10;
	events.xp_timestamp = 1;

	EXPECT_TRUE(apply_xp(&game_state, events));
	EXPECT_EQ(1, game_state.persistent.last_recorded_xp_update);
	EXPECT_EQ(10, game_state.persistent.xp);
	EXPECT_EQ(LifeStage::CHILD, game_state.persistent.stage);
}

TEST_F(TestXpManagement, check_xp__too_soon_0_events_only_updates_event_timestamp) {
	GameEvents events;
	events.xp = 0;
	events.xp_timestamp = 0;

	game_state.persistent.last_recorded_xp_update = 1;

	check_xp(&game_state, 1, &events);

	EXPECT_EQ(1, events.xp_timestamp);
	EXPECT_EQ(0, events.xp);
}

TEST_F(TestXpManagement, check_xp__1_event_random_skips_xp) {
	GameEvents events;
	events.xp = 0;
	events.xp_timestamp = 1;

	game_state.persistent.last_recorded_xp_update = 0;
	random_controller.set_next_random(NEW_XP_PROBABILITY + 1);

	check_xp(&game_state, NEW_XP_FREQUENCY, &events);

	EXPECT_EQ(NEW_XP_FREQUENCY, events.xp_timestamp);
	EXPECT_EQ(0, events.xp);
}

TEST_F(TestXpManagement, check_xp__1_event_random_assigns_xp) {
	GameEvents events;
	events.xp = 0;
	events.xp_timestamp = 1;

	game_state.persistent.last_recorded_xp_update = 0;
	random_controller.set_next_random(0);

	check_xp(&game_state, NEW_XP_FREQUENCY, &events);

	EXPECT_EQ(NEW_XP_FREQUENCY, events.xp_timestamp);
	EXPECT_EQ(1, events.xp);
}

TEST_F(TestXpManagement, check_xp__3_events) {
	GameEvents events;
	events.xp = 0;
	events.xp_timestamp = 1;

	game_state.persistent.last_recorded_xp_update = 0;
	random_controller.set_next_randoms({0, NEW_XP_PROBABILITY + 1, 0});

	check_xp(&game_state, NEW_XP_FREQUENCY * 3, &events);

	EXPECT_EQ(NEW_XP_FREQUENCY * 3, events.xp_timestamp);
	EXPECT_EQ(2, events.xp);
}
