#pragma once

#include "Globals.h"


struct Polyomino {
	Polyomino() = delete; // no default constructor

	Polyomino(int mino);

	void setPolyomino(int mino);

	std::vector<Point> data;
	int x, y;
	int minoIndex;
	int rotation;

};