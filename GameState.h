#pragma once


#include "Globals.h"
#include "Polyomino.h"

struct GameState {

	int matrix[Globals::WIDTH][Globals::HEIGHT];
	//std::vector<int> incomingGarbage;

	int hold;
	bool canHold;

	GameState();

	bool performHold(GameState& state, Polyomino& mino, std::vector<int>& next);

	bool matrixContains(const Polyomino& mino);

	// moves down one
	// retruns whether it succeeded
	bool softDrop(Polyomino& mino);

	// moves tetromino all the way down and pastes it to the matrix
	int  hardDrop(Polyomino& mino);

	// returns lines cleared
	// must manually call
	int clearLines();


	void hardDropWithoutPaste(Polyomino& mino);

	// moves specified amount
	// -1 for left, 1 for right
	// return whether it succeeded
	bool moveX(Polyomino& mino, int x);

	// if -1, move all the way left
	// if 1, move all the way right
	void arrX(Polyomino& mino, int x);

	// rotates in specified direction
	// 1 for clockwise
	// -1 for counterclockwise
	void rotate(Polyomino& mino, int dir);


	// resets the matrix to all -1s
	void resetMatrix();

	friend bool operator== (const GameState& state1, const GameState& state2);

private:
	void pasteToMatrix(const Polyomino& mino);

	bool wallKick(Polyomino& mino, int dir);


public:
	static void pushOntoNextlist(std::vector<int>& next) {
		int s = Globals::polyominoes.size();

		std::vector<int> nums; nums.reserve(s);
		for (int i = 0; i < s; ++i) nums.push_back(i);
		std::random_shuffle(nums.begin(), nums.end());
		next.reserve(s);
		for (size_t i = 0; i < nums.size(); ++i) {
			next.push_back(nums[i]);
		}
	}

};