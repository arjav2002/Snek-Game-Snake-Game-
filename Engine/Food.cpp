#include "Food.h"

#include <random>

bool Food::obstacleInTile(Location& tileLoc, const Obstacle obstacles[], const int currentObstacles) {
	for (int i = 0; i < currentObstacles; i++) {
		if (obstacles[i].loc == tileLoc)
			return true;
	}
	return false;
}

Food::Food(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacle obstacles[], const int currentObstacles) {
	respawn(rng, brd, snek, obstacles, currentObstacles);
}

void Food::draw(Board & brd) const {
	brd.drawCell(loc, c);
}

void Food::respawn(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacle obstacles[], const int currentObstacles) {
	std::uniform_int_distribution<int> xDist(0, brd.getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.getHeight() - 1);

	do {
		loc.x = xDist(rng);
		loc.y = yDist(rng);
	} while (snek.isInTile(loc) || obstacleInTile(loc, obstacles, currentObstacles));
}