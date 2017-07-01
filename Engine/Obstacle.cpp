#include "Obstacle.h"
#include "Snake.h"

bool Obstacle::locationIsValid(const Obstacle obstacles[], const int currentObstacles, const Snake& snek) {
	for (int i = 0; i < currentObstacles - 1; i++) {
		if (loc == obstacles[i].loc)
			return false;
	}
	return !(snek.isInTile(loc));
}