#pragma once

#include <cstdint>
#include <deque>
#include <initializer_list>

class RandomController {
	public:
		RandomController();
		void set_next_random(uint32_t next_random);
		void set_next_randoms(std::initializer_list<uint32_t> next_randoms);
		uint32_t get_random();
	
	private:
		std::deque<uint32_t> _next_random;
};
