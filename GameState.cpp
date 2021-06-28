#include "GameState.h"



bool operator==(const GameState& state1, const GameState& state2) {
	return (state1.matrix == state2.matrix &&
		state1.canHold == state2.canHold &&
		state1.hold == state2.hold
		);
}



GameState::GameState() :
	hold{ -1 },
	canHold{ true } {

	//memset(matrix, -1, sizeof(int)* Globals::WIDTH * Globals::HEIGHT);

}



// returns whether it could and also performs the hold
bool GameState::performHold(GameState& state, Polyomino& mino, std::vector<int>& next) {
	if (canHold) {
		int newHold = mino.minoIndex;
		if (!(state.hold >= 0 && state.hold < (int)Globals::polyominoes.size())) {
			mino.setPolyomino(next.front());
			next.erase(next.begin());
		}
		else {
			mino.setPolyomino(state.hold);
		}
		state.hold = newHold;
		canHold = false;
		return true;
	}
	return false;

}


// check if a tetromino is inside of a block of the matrix
bool GameState::matrixContains(const Polyomino& mino) {
	bool contains = false;

	// check the coordinates of each tile of the tetromino
	// if the cooresponding tile of the Matrix is a block, return true
	for (size_t i = 0; i < mino.data.size(); ++i) {
		int x = mino.data[i].x + mino.x;
		int y = mino.data[i].y + mino.y;


		if (x >= Globals::WIDTH || x < 0 || y >= Globals::HEIGHT) // check if it's out of bounds
			contains = true;
		else if (y >= 0)
			if (matrix[x][y] >= 0)
				contains = true;

	}
	return contains;
}


// returns if it succeded
bool GameState::softDrop(Polyomino& mino) {
	mino.y++;
	if (matrixContains(mino)) {
		mino.y--;
		return false;
	}
	else {
		return true;
	}
}

// moves the tetromino down as far as it can go an then pastes it to the matrix
// returns how far it moved down
int GameState::hardDrop(Polyomino& mino) {
	canHold = true;
	for (int i = 0; i < Globals::HEIGHT + 10; i++) {
		mino.y++;
		if (matrixContains(mino)) {
			// if the hard drop moved the tetromino, the last move wasn't a kick
			mino.y--;
			pasteToMatrix(mino);
			return i;
			break;
		}
	}
	return 0;
}


int GameState::clearLines() {
	int c;
	int lines{ 0 };
	for (int i = 0; i < Globals::HEIGHT; ++i) {
		c = 0;
		//std::cout << std::endl;
		for (int j = 0; j < Globals::WIDTH; ++j) {
			if (matrix[j][i] > -1) c++;
			//std::cout << grid[i][j] << " ";
		}

		if (c == Globals::WIDTH) {
			lines++;
			// Move the rest down
			for (int y = i; y >= 0; --y) {
				for (int x = 0; x < Globals::WIDTH; ++x) {
					if (y - 1 < 0) matrix[x][y] = -1;
					else matrix[x][y] = matrix[x][y - 1];

				}
			}
		}
		//std::cout << c << " ";
	}

	return lines;
}



void GameState::hardDropWithoutPaste(Polyomino& mino) {
	for (int i = 0; i < Globals::HEIGHT; i++) {
		mino.y++;
		if (matrixContains(mino)) {
			mino.y--;
			break;
		}
	}
}


void GameState::pasteToMatrix(const Polyomino& mino) {
	for (size_t i = 0; i < mino.data.size(); ++i) {
		int x = mino.data[i].x + mino.x;
		int y = mino.data[i].y + mino.y;
		if (x >= 0 && x < Globals::WIDTH && y >= 0 && y < Globals::HEIGHT) {
			matrix[x][y] = mino.minoIndex;
		}
	}
}

// 0 doesn't move it at all
// if the movement fails, it moves it back to where it was
bool GameState::moveX(Polyomino& mino, int x) {
	mino.x += x;
	if (matrixContains(mino)) {
		mino.x -= x;
		return false;
	}
	else {
		return true;
	}
}

void GameState::arrX(Polyomino& mino, int x) {
	for (int i = 0; i < Globals::WIDTH; ++i) {
		moveX(mino, x);
	}
}

// 0 doesn't rotate, 1 rotates right, -1 rotates left
// 2 rotates 180 degrees
void GameState::rotate(Polyomino& mino, int dir) {
	Polyomino oldMino{ mino };


	if (dir == 1) {
		for (size_t i = 0; i < mino.data.size(); ++i) {
			int x = mino.data[i].x; int y = mino.data[i].y;
			mino.data[i].x = y * -1;
			mino.data[i].y = x;
		}
	}
	if (dir == -1) {
		for (size_t i = 0; i < mino.data.size(); ++i) {
			int x = mino.data[i].x; int y = mino.data[i].y;
			mino.data[i].x = y;
			mino.data[i].y = x * -1;
		}
	}
	if (dir == 2) {
		for (size_t i = 0; i < mino.data.size(); ++i) {
			int x = mino.data[i].x; int y = mino.data[i].y;
			mino.data[i].x = y;
			mino.data[i].y = x * -1;
		}
		for (size_t i = 0; i < mino.data.size(); ++i) {
			int x = mino.data[i].x; int y = mino.data[i].y;
			mino.data[i].x = y;
			mino.data[i].y = x * -1;
		}
	}

	bool kickSuccess = false;
	if (matrixContains(mino)) kickSuccess = wallKick(mino, dir);
	// if it doesn't work, undo it
	if (matrixContains(mino) && !kickSuccess) {
		for (size_t i = 0; i < mino.data.size(); ++i) {
			mino.data[i].x = oldMino.data[i].x;
			mino.data[i].y = oldMino.data[i].y;
		}
	}
	else {
		if (dir == 2) {
			if (mino.rotation == 0) mino.rotation = 2;
			if (mino.rotation == 1) mino.rotation = 3;
			if (mino.rotation == 2) mino.rotation = 0;
			if (mino.rotation == 3) mino.rotation = 1;
		}
		else {
			mino.rotation += dir;
		}
		if (mino.rotation < 0) mino.rotation = 3;
		if (mino.rotation > 3) mino.rotation = 0;
	}
}


// not currently functional
bool GameState::wallKick(Polyomino& mino, int dir) {
	int newRotation = mino.rotation;

	newRotation += dir;
	if (newRotation < 0) newRotation = 3;
	if (newRotation > 3) newRotation = 0;


	int storeX = mino.x; int storeY = mino.y;

	std::vector<Point> kicks;
	for (int i = -4; i < 4; ++i) 
		for (int j = -4; j < 4; ++j) 
			kicks.push_back({ i, j });

	// sort them so it tries the smallest movements first
	for (size_t i = 0; i < kicks.size(); ++i)
		for (size_t j = i; j < kicks.size(); ++j)
			if (abs(kicks[i].x) + abs(kicks[i].y) > abs(kicks[j].x) + abs(kicks[j].y)) {
				Point t = kicks[i];
				kicks[i] = kicks[j];
				kicks[j] = t;
			}

	


	for (size_t i = 0; i < kicks.size(); ++i) {
		mino.x += kicks[i].x;
		mino.y += kicks[i].y;

		if (!matrixContains(mino)) {
			return true;
		}
		else {
			mino.x = storeX;
			mino.y = storeY;
		}
	}

	return false;
	
}




void GameState::resetMatrix() {
	for (int i = 0; i < Globals::WIDTH; ++i) {
		for (int j = 0; j < Globals::HEIGHT; ++j) {
			matrix[i][j] = -1;
		}
	}
}