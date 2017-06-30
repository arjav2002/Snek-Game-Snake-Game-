#include "Board.h"

Board::Board(Graphics& _gfx) :
	gfx(_gfx)
{}

void Board::drawCell(const Location& loc, const Color c) {
	if(loc.x < 0 ||
	   loc.x >= width ||
	   loc.y < 0 ||
	   loc.y >= height) return;
	int paddingX = 3, paddingY = 3;
	gfx.DrawRectDim(loc.x * cellSide + paddingX + xOffset, loc.y * cellSide + paddingY + yOffset, cellSide - paddingX, cellSide - paddingY, c);
}

void Board::drawBoundary() {
	int top = yOffset;
	int bottom = yOffset + height * cellSide;
	int left = xOffset;
	int right = xOffset + width * cellSide;

	gfx.DrawRectDim(left, top, right - left, cellSide, {0, 0, 255});
	gfx.DrawRectDim(left, top + cellSide, cellSide, bottom - top - 2 * cellSide, { 0, 0, 255 });
	gfx.DrawRectDim(right - cellSide, top + cellSide, cellSide, bottom - top - 2 * cellSide, { 0, 0, 255 });
	gfx.DrawRectDim(left, bottom - cellSide, right - left, cellSide, { 0, 0, 255 });
}