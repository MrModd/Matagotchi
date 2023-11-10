#include "game/random_generator.h"
#include "mocks/game/random_controller.h"

extern RandomController random_controller;

uint32_t random_uniform(uint32_t min, uint32_t max) {
    return (random_controller.get_random() % (max - min)) + min;
}

bool toss_a_coin(uint32_t probability) {
    furi_assert(100 >= probability);
    return random_uniform(1, 101) <= probability;
}
