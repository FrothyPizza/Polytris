#include "PlayerGame.h"


PlayerGame::PlayerGame() : 
	gameState{}, 
	curMino{ NULL }, 
	rect{}  {


	for (int i = 0; i < 5; ++i) GameState::pushOntoNextlist(nextList);


	curMino.setPolyomino(nextList.front());
	nextList.erase(nextList.begin());

}

void PlayerGame::render(sf::RenderWindow* window, sf::Vector2f position, float tileSize) {
	renderPolytris(window, position, tileSize, rect, gameState, curMino, nextList);
}

void PlayerGame::inputRight(bool rightPressed) {
	if (rightPressed && RclockRestarted == false) {
		Rclock.restart();
		RclockRestarted = true;
		gameState.moveX(curMino, 1);
	}
	else {
		if (rightPressed == false) RclockRestarted = false;
	}
	if (Rclock.getElapsedTime().asMilliseconds() > das && rightPressed) {
		gameState.arrX(curMino, 1);
		LclockRestarted = false;
	}



}

void PlayerGame::inputLeft(bool leftPressed) {
	if (leftPressed && LclockRestarted == false) {
		Lclock.restart();
		LclockRestarted = true;
		gameState.moveX(curMino, -1);
	}
	else {
		if (leftPressed == false) LclockRestarted = false;
	}
	if (Lclock.getElapsedTime().asMilliseconds() > das && leftPressed) {
		//m_gameState.moveX(m_currentTetromino, -1);
		gameState.arrX(curMino, -1);
		RclockRestarted = false;
	}
}

void PlayerGame::inputDown() {
	gameState.hardDropWithoutPaste(curMino);
}

int PlayerGame::inputGeneral(int keyCode) {
	// hard drop
	if (keyCode == sf::Keyboard::Space) {
		int mino = curMino.minoIndex;
		gameState.hardDrop(curMino);
		curMino.setPolyomino(nextList.front());
		nextList.erase(nextList.begin());
		if (nextList.size() < Globals::PREVIEWS * 2) GameState::pushOntoNextlist(nextList);
		gameState.clearLines();
		
	}

	if (keyCode == sf::Keyboard::C) {
		gameState.performHold(gameState, curMino, nextList);
	}
	if (keyCode == sf::Keyboard::Up) {
		gameState.rotate(curMino, 1);
	}
	if (keyCode == sf::Keyboard::Z) {
		gameState.rotate(curMino, -1);
	}
	if (keyCode == sf::Keyboard::X) {
		gameState.rotate(curMino, 2);
	}
	if (keyCode == sf::Keyboard::Q) {
		gameState.resetMatrix();
	}



	return 0;
}

