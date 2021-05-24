#include "Render.h"

#include <iostream>


void setColor(sf::RectangleShape& rect, int tileIndex) {

	int index = tileIndex;
	std::vector<int> digits;
	if (index == 0) digits.push_back(0);
	while (index > 0) {
		int digit = index % 10;
		index /= 10;
		digits.push_back(digit);
	}
	int r, g, b;
	if (digits.size() >= 3) {
		r = digits[0] * 25;
		g = digits[1] * 25;
		b = digits[2] * 25;
	}
	else if (digits.size() == 2) {
		r = digits[0] * 25;
		g = digits[1] * 25;
		b = tileIndex*2;
	}
	else {
		r = digits[0] * 12;
		g = (tileIndex % 3) * 20;
		b = (tileIndex % 2 + 1) * tileIndex*5;
	}

	rect.setFillColor(sf::Color(255-r, 255-g, 255-b));

}



void renderPolytris(sf::RenderWindow* window, sf::Vector2f position, float tileSize, sf::RectangleShape& tile,
	GameState& gameState, const Polyomino& mino, std::vector<int>& nextList) {

	tile.setSize(sf::Vector2f(tileSize, tileSize));

	// Draw matrix
	// don't render the top two tiles
	for (int i = 0; i < Globals::WIDTH; ++i) {
		for (int j = 0; j < Globals::HEIGHT; ++j) {
			if (gameState.matrix[i][j] > -1) {
				tile.setPosition(sf::Vector2f(tileSize * i, tileSize * (j - Globals::YMARGIN)) + position);
				setColor(tile, gameState.matrix[i][j]);
				window->draw(tile);
			}
		}
	}


	// Draw lines of the matrix
	sf::RectangleShape verticalLine{ sf::Vector2f(1.f, (Globals::HEIGHT - Globals::YMARGIN) * tileSize) };
	sf::RectangleShape horizontalLine{ sf::Vector2f((Globals::WIDTH)*tileSize, 1.f) };
	verticalLine.setFillColor(sf::Color(255, 255, 255, 30));
	horizontalLine.setFillColor(sf::Color(255, 255, 255, 30));
	for (int i = 0; i < Globals::WIDTH + 1; ++i) {
		if (i == 0 || i == Globals::WIDTH) 	verticalLine.setFillColor(sf::Color(255, 255, 255));
		else 	verticalLine.setFillColor(sf::Color(255, 255, 255, 30));
		verticalLine.setPosition(sf::Vector2f(i * tileSize, 0) + position);
		window->draw(verticalLine);
	}
	for (int i = 0; i < Globals::HEIGHT - Globals::YMARGIN + 1; ++i) {
		if (i == 0 || i == Globals::HEIGHT - Globals::YMARGIN) horizontalLine.setFillColor(sf::Color(255, 255, 255, 255));
		else 	horizontalLine.setFillColor(sf::Color(255, 255, 255, 30));
		horizontalLine.setPosition(sf::Vector2f(0, i * tileSize) + position);
		window->draw(horizontalLine);
	}





	// Draw ghost
	Polyomino ghost{ mino };
	gameState.hardDropWithoutPaste(ghost);
	for (size_t i = 0; i < ghost.data.size(); ++i) {
		tile.setFillColor(sf::Color(125, 125, 125, 125));
		tile.setPosition(sf::Vector2f(tileSize * (ghost.x + ghost.data[i].x),
			tileSize * (ghost.y + ghost.data[i].y - Globals::YMARGIN)) + position);
		window->draw(tile);
	}

	// Draw current tetromino
	for (size_t i = 0; i < mino.data.size(); ++i) {
		setColor(tile, mino.minoIndex);
		tile.setPosition(sf::Vector2f(tileSize * (mino.x + mino.data[i].x),
			tileSize * (mino.y + mino.data[i].y - Globals::YMARGIN)) + position);
		window->draw(tile);
		
	}


	// Draw next list
	Polyomino next{ NULL };
	for (int i = 0; i < Globals::PREVIEWS; ++i) {
		next.setPolyomino(nextList.at(i));
		next.x = Globals::WIDTH + 3; next.y = Globals::YMARGIN + i * 6;
		sf::Vector2f posModifier{};
		for (size_t i = 0; i < next.data.size(); ++i) {
			setColor(tile, next.minoIndex);
			tile.setPosition(sf::Vector2f(tileSize * (next.x + next.data[i].x),
				tileSize * (next.y + next.data[i].y - Globals::YMARGIN)) + position + posModifier * tileSize);
			window->draw(tile);
		}
	}

	// Draw hold
	if (gameState.hold >= 0 && gameState.hold < (int)Globals::polyominoes.size()) {
		Polyomino hold{ gameState.hold };
		hold.x = -4;
		hold.y = Globals::YMARGIN + 1;
		for (size_t i = 0; i < hold.data.size(); ++i) {
			setColor(tile, hold.minoIndex);
			tile.setPosition(sf::Vector2f(tileSize * (hold.x + hold.data[i].x),
				tileSize * (hold.y + hold.data[i].y - Globals::YMARGIN)) + position);
			window->draw(tile);
		}
	}




}
