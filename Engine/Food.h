#pragma once

#include "Board.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include "Obstacle.h"

#include <random>

class Food {
private:
	Location loc;
	static constexpr Color c = Colors::Red;

private:
	bool obstacleInTile(Location& tileLoc, const Obstacle obstacles[], const int currentObstacles);

public:
	Food(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacle obstacles[], const int currentObstacles);

	void draw(Board& brd) const;
	void respawn(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacle obstacles[], const int currentObstacles);

	Location getLocation() { return loc; }
};