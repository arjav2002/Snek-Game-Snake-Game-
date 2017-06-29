#include "Board.h"

Board::Board(Graphics& _gfx) :
	gfx(_gfx)
{}

void Board::drawCell(const Location & loc, const Color c) {
	if(loc.x < 0 ||
	   loc.x >= width ||
	   loc.y < 0 ||
	   loc.y >= height) return;
	int paddingX = 3, paddingY = 3;
	gfx.DrawRectDim(loc.x * cellSide + paddingX, loc.y * cellSide + paddingY, cellSide - paddingX, cellSide - paddingY, c);
}