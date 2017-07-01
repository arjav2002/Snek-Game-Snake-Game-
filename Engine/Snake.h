#pragma once

#include "Board.h"
#include "Location.h"
#include "Obstacle.h"

class Snake {
private:
	class Segment {
	private:
		Location loc;
		char gridWidth, gridHeight;
		bool initialized = false;
	public:
		void init(const Location& _loc, const char _gridWidth, const char _gridHeight);
		void draw(Board& brd, const Color c);
		void follow(const Segment& segment);
		void moveBy(const Location& location);

		Location getLocation() const { return loc; }
	};
private:
	void move(const Location& loc);
private:
	int currentSegments = 3;
	Board& brd;
	static constexpr int maxSegments = 40 * 30, nSegmentColors = 4;
	Segment segments[maxSegments];
	Color segmentColors[nSegmentColors] = { {10, 100, 32}, {10, 130, 48}, {18, 160, 48}, { 10, 130, 48 } };
	Color headColor = { 255, 255, 0 };
	char direction = 0; // 0->left 1->up 2->right 3->down (clockwise)
	bool HasBangedIntoWall = false, IsHeadEatingBody = false, HasBangedIntoObstacle = false;
public:
	Snake(Location& loc, Board& _brd);
	void draw(Board& brd);
	void grow();
	void update(const Obstacle obstacles[], const int currentObstacles);
	bool isInTile(const Location& tile) const;
	char getDirection() const { return direction; }
	void setDirection(const char dir) { direction = dir; }
	Location getHeadLocation() const { return segments[0].getLocation(); }
	bool isHeadEatingBody() const { return IsHeadEatingBody; }
	bool hasBangedIntoWall() const { return HasBangedIntoWall; }
	bool hasBangedIntoObstacle() const { return HasBangedIntoObstacle; };
};