#pragma once

#include "Board.h"
#include "Location.h"

#include <random>

class Snake;

class Obstacle {
public:
	Location loc;
	static constexpr Color obstacleColor = Colors::Gray;

private:
	bool locationIsValid(const Obstacle obstacles[], const int currentObstacles, const Snake& snek);

public:
	void init(std::mt19937& rng, const Board& brd, const Obstacle obstacles[], const int currentObstacles, const Snake& snek) {
		std::uniform_int_distribution<int> xDist(0, brd.getWidth() - 1), yDist(0, brd.getHeight() - 1);
		do {
			loc.x = xDist(rng);
			loc.y = yDist(rng);
		} while (!locationIsValid(obstacles, currentObstacles, snek));
	}
	void draw(Board& brd) { brd.drawCell(loc, obstacleColor); }
};