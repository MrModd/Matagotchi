#include "random_controller.h"

RandomController random_controller;

RandomController::RandomController() {
	set_next_random(0);
}

void RandomController::set_next_random(uint32_t next_random) {
	_next_random.emplace_front(next_random);
}

void RandomController::set_next_randoms(std::initializer_list<uint32_t> next_randoms) {
	_next_random = next_randoms;
}

uint32_t RandomController::get_random() {
	if(_next_random.size() == 0) return 0;

	uint32_t ret = _next_random.front();
	_next_random.pop_front();

	return ret;
}
