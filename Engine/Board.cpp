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
	int left = xOffset;
	int top = yOffset;
	int bottom = yOffset + height * cellSide;
	int right = xOffset + width * cellSide;

	// top
	gfx.DrawRect(left - borderWidth, top - borderWidth, right + borderWidth, top - borderPadding, borderColor);

	// left
	gfx.DrawRect(left - borderWidth, top - borderPadding, left - borderPadding, bottom + borderPadding, borderColor);

	// bottom
	gfx.DrawRect(left - borderWidth, bottom + borderPadding, right + borderWidth, bottom + borderWidth, borderColor);

	// right
	gfx.DrawRect(right + borderWidth, top - borderPadding, right + borderPadding, bottom + borderPadding, borderColor);
}