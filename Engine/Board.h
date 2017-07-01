#pragma once

#include "Graphics.h"
#include "Location.h"

class Board {
private:
	static constexpr int cellSide = 20, width = 30, height = 25;
	Graphics& gfx;

	static constexpr int xOffset = 95, yOffset = 50;
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int borderWidth = 5, borderPadding = 2;
	// border padding only refers to areas surrounding the gameplay not the ones on the outer side
public:
	Board(Graphics& _gfx);
	void drawCell(const Location& loc, const Color c);
	void drawBoundary();

	int getHeight() const { return height; }
	int getWidth() const { return width; }
	int getSide() const { return cellSide; }
};