#include "Polyomino.h"


Polyomino::Polyomino(int mino) :
	minoIndex{ mino }, data{ } {

	x = Globals::WIDTH / 2;
	y = Globals::YMARGIN - Globals::TETROMINO_START_Y;
	rotation = 0;

	data.reserve(Globals::POLY_SIZE);
	for (size_t i = 0; i < Globals::polyominoes[minoIndex].size(); ++i) {
		data.push_back(Globals::polyominoes[minoIndex][i]);
	}
}

// resets the tetromino x, y, and rotation and makes it the new tetromino
void Polyomino::setPolyomino(int mino) {
	minoIndex = mino;
	x = Globals::WIDTH/2;
	y = Globals::YMARGIN - Globals::TETROMINO_START_Y;
	rotation = 0;

	for (size_t i = 0; i < Globals::polyominoes[minoIndex].size(); ++i) {
		data[i] = Globals::polyominoes[minoIndex][i];
	}
}