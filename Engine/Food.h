#pragma once

#include "Board.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"

#include <random>

class Food {
private:
	Location loc;
	static constexpr Color c = Colors::Red;
public:
	Food(std::mt19937& rng, const Board& brd, const Snake& snek);

	void draw(Board& brd) const;
	void respawn(std::mt19937& rng, const Board& brd, const Snake& snek);

	Location getLocation() { return loc; }
};