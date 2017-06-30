#pragma once

#include "Graphics.h"
#include "Location.h"

class Board {
private:
	static constexpr int cellSide = 20, width = 40, height = 30;
	Graphics& gfx;
public:
	Board(Graphics& _gfx);
	void drawCell(const Location& loc, const Color c);
	void drawBoundary();

	int getHeight() const { return height; }
	int getWidth() const { return width; }
	int getSide() const { return cellSide; }
};