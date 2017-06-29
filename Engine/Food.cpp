#include "Food.h"

#include <random>

Food::Food(std::mt19937& rng, const Board& brd, const Snake& snek) {
	respawn(rng, brd, snek);
}

void Food::draw(Board & brd) const {
	brd.drawCell(loc, c);
}

void Food::respawn(std::mt19937& rng, const Board& brd, const Snake& snek) {
	std::uniform_int_distribution<int> xDist(1, brd.getWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.getHeight() - 2);

	do {
		loc.x = xDist(rng);
		loc.y = yDist(rng);
	} while (snek.isInTile(loc));
}