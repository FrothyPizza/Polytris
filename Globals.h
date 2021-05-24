#pragma once


#include <vector>
#include <array>
#include <random>

struct Point {
	int x, y;
};

class Globals {
public:

	static void InitVars();

	static std::vector<std::vector<Point>> polyominoes;
	static const size_t POLY_SIZE{ 11 };

	static const int WIDTH{ 20 };
	static const int HEIGHT{ 40 };
	static const int YMARGIN{ HEIGHT - 40 };
	static const int TETROMINO_START_Y{ 0 };
	static const int DAS{ 70 };
	static const int PREVIEWS{ 3 };



};

