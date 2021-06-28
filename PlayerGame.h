#pragma once

#include "Globals.h"
#include "GameState.h"
#include "SFML/Graphics.hpp"
#include "Render.h"


class PlayerGame {
private:
	// stuff to handle timing
	sf::Clock Rclock;
	bool RclockRestarted{ false };
	sf::Clock Lclock;
	bool LclockRestarted{ false };
	sf::Clock LARRClock;
	sf::Clock RARRClock;
	sf::Clock SDFClock;


public:
	int das{ Globals::DAS };
	int arr{ Globals::ARR };
	int sdf{ Globals::SDF };

	std::vector<int> nextList;
	Polyomino curMino;
	GameState gameState;

	sf::RectangleShape rect;

	PlayerGame();

	void render(sf::RenderWindow* window, sf::Vector2f position, float tileSize);

	// right and left inputs are separated from general because they need to be handled differently
	void inputRight(bool rightPressed, bool leftPressed);

	// right and left inputs are separated from general because they need to be handled differently
	void inputLeft(bool leftPressed, bool rightPressed);

	// soft drops all the way
	void inputDown();

	// any input not left or right
	// returns how many lines are sent, if any
	int inputGeneral(int keyCode);


};

