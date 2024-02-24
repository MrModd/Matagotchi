#ifndef __STATE_MANAGEMENT_H__
#define __STATE_MANAGEMENT_H__

#include <stdint.h>

#include "flipper_structs.h"
#include "game_structs.h"

void init_state(struct ApplicationContext *);
void persist_state(struct GameState *);
void reset_state(struct GameState *);
void generate_new_random_events(struct ApplicationContext *, struct GameEvents *);
/* Returns true if the game state has been updated */
bool process_events(struct ApplicationContext *, struct GameEvents);
/* Get a string that can be used to show the game state */
void get_state_str(const struct GameState *, char *, size_t);
/* Restore some HU with a candy (user event) */
void give_candy(struct GameState *, struct GameEvents *);
/* Restore some HP with a pill (user event) */
void give_pill(struct GameState *, struct GameEvents *);

#endif
