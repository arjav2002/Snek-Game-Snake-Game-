#pragma once

class Location {
public:
	int x, y;
	void add(const Location& loc) {
		x += loc.x;
		y += loc.y;
	}
	Location operator+(const Location& loc) {
		Location result;
		result.x = x + loc.x;
		result.y = y + loc.y;
		return result;
	}
	bool operator==(const Location& loc) const {
		return x == loc.x && y == loc.y;
	}
};