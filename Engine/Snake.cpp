#include "Snake.h"
#include "Game.h"

#include <assert.h>

Snake::Snake(Location& loc, Board& _brd) : brd(_brd) {
	segments[0].init(loc, brd.getWidth(), brd.getHeight());
	segments[1].init({ loc.x + 1, loc.y }, brd.getWidth(), brd.getHeight());
	segments[2].init({ loc.x + 2, loc.y }, brd.getWidth(), brd.getHeight());
}

void Snake::draw(Board& brd) {
	for (int i = currentSegments - 1; i >= 0; i--) {
		if (i == 0) segments[i].draw(brd, headColor);
		else segments[i].draw(brd, segmentColors[(i - 1) % nSegmentColors]);
	}
}

void Snake::grow() {
	assert(currentSegments < maxSegments);
	Location newLoc(segments[currentSegments-1].getLocation());
	segments[currentSegments++].init(newLoc, brd.getWidth(), brd.getHeight());
}

void Snake::update(const Obstacle obstacles[], const int currentObstacles) {
	Location deltaLoc;
	if (direction == 0) {
		deltaLoc.x = -1;
		deltaLoc.y = 0;
	}
	else if (direction == 1) {
		deltaLoc.x = 0;
		deltaLoc.y = -1;
	}
	else if (direction == 2) {
		deltaLoc.x = 1;
		deltaLoc.y = 0;
	}
	else if (direction == 3) {
		deltaLoc.x = 0;
		deltaLoc.y = 1;
	}

	Location resultantLoc = segments[0].getLocation() + deltaLoc;

	HasBangedIntoWall = resultantLoc.x < 0 || resultantLoc.y < 0 || 
						resultantLoc.x > brd.getWidth() - 1 || resultantLoc.y > brd.getHeight() - 1;

	for (int i = 1; i < currentSegments; i++) {
		if (resultantLoc == segments[i].getLocation()) {
			IsHeadEatingBody = true;
			break;
		}			
	}

	for (int i = 0; i < currentObstacles; i++) {
		if (resultantLoc == obstacles[i].loc) {
			HasBangedIntoObstacle = true;
			break;
		}
	}

	if (HasBangedIntoWall || IsHeadEatingBody || HasBangedIntoObstacle)
		return;

	move(deltaLoc);
}

void Snake::move(const Location& deltaLoc) {
	

	// loop through all the segments except the first one
	for (int i = currentSegments - 1; i > 0; i--) {
		segments[i].follow(segments[i - 1]);
	}

	segments[0].moveBy(deltaLoc);
}

bool Snake::isInTile(const Location& tile) const {
	for (int i = 0; i < currentSegments; i++) {
		if (tile == segments[i].getLocation())
			return true;
	}
	return false;
}

void Snake::Segment::draw(Board& brd, const Color c) {
	brd.drawCell(loc, c);
}

void Snake::Segment::init(const Location& _loc, const char _gridWidth, const char _gridHeight) {
	assert(!initialized);
	loc = _loc;
	gridWidth = _gridWidth;
	gridHeight = _gridHeight;
	initialized = true;
}

void Snake::Segment::follow(const Segment& segment) {
	loc = segment.loc;
}

void Snake::Segment::moveBy(const Location& location) {
	assert(abs(location.x) + abs(location.y) == 1); // you moved too much for one function call
	loc.add(location);
}
