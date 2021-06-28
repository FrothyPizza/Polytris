#pragma once


#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

struct Point {
	int x, y;

	bool operator== (const Point& other) const {
		return (this->x == other.x && this->y == other.y);
	}
};

class Globals {
private:
	static void InitAllKeys();
	static std::unordered_map<std::string, sf::Keyboard::Key> ALL_KEYS;

public:
	static std::unordered_map<std::string, sf::Keyboard::Key> CONTROLS;

	
	static void InitVars();

	static std::vector<std::vector<Point>> polyominoes;
	static size_t POLY_SIZE;

	//static std::vector<Point> generateRandomPolyomino(std::vector<Point> polyomino = { {0, 0} }, int n = 0);
	static std::vector<Point> generateRandomPolyomino();

	// if the polyomino size is really large and it takes seconds to generate a single one,
	// then the user should call this asynchrounously after every hard drop
	static void addPolyominoToPool() {
		polyominoes.push_back(generateRandomPolyomino());
		std::cout << "Added polyomino\n";
	}

	static int WIDTH;
	static int HEIGHT;
	static int YMARGIN;

	//static const int WIDTH{ 10 };
	//static const int HEIGHT{ 25 };
	//static const int YMARGIN{ HEIGHT - 20 }; // HEIGHT-40
	static const int TETROMINO_START_Y{ 0 };
	static int DAS;
	static int ARR;
	static int PREVIEWS;
	static int SDF;



};

