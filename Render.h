#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"


void renderPolytris(sf::RenderWindow* window, sf::Vector2f position, float tileSize, sf::RectangleShape& tile
	, GameState& gameState, const Polyomino& mino, std::vector<int>& nextList);
