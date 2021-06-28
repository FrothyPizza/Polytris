#include "PlayerGame.h"

#include <iostream>
#include <future>


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



//void PlayerGame::inputRight(bool rightPressed) {
//	if (rightPressed && RclockRestarted == false) {
//		Rclock.restart();
//		RclockRestarted = true;
//		gameState.moveX(curMino, 1);
//	}
//	else {
//		if (rightPressed == false) RclockRestarted = false;
//	}
//	if (arr > 0) {
//		if (Rclock.getElapsedTime().asMilliseconds() > das && rightPressed) {
//			if (ARRClock.getElapsedTime().asMilliseconds() > 0) {
//				ARRClock.restart();
//				gameState.moveX(curMino, 1);
//			}
//
//		}
//	}
//	else {
//		gameState.arrX(curMino, -1);
//		RclockRestarted = false;
//	}
//}
//
//void PlayerGame::inputLeft(bool leftPressed) {
//	if (leftPressed && LclockRestarted == false) {
//		Lclock.restart();
//		LclockRestarted = true;
//		gameState.moveX(curMino, -1);
//	}
//	else {
//		if (leftPressed == false) LclockRestarted = false;
//	}
//	if (arr > 0) {
//		if (Lclock.getElapsedTime().asMilliseconds() > das && leftPressed) {
//			if (ARRClock.getElapsedTime().asMilliseconds() > 0) {
//				ARRClock.restart();
//				gameState.moveX(curMino, -1);
//			}
//		}
//	}
//	else {
//		gameState.arrX(curMino, -1);
//		RclockRestarted = false;
//	}
//}
//
//void PlayerGame::inputDown() {
//	gameState.hardDropWithoutPaste(curMino);
//}

void PlayerGame::inputRight(bool rightPressed, bool leftPressed) {
	//if (leftPressed) return;
	if (leftPressed && RARRClock.getElapsedTime().asMilliseconds() > 0 && rightPressed) {
		Lclock.restart();
	}


	if (rightPressed && RclockRestarted == false) {
		Rclock.restart();
		RclockRestarted = true;
		gameState.moveX(curMino, 1);

	}
	else {
		if (rightPressed == false) RclockRestarted = false;
	}
	if (arr > 0) {
		if (Rclock.getElapsedTime().asMilliseconds() > das && rightPressed) {
			if (RARRClock.getElapsedTime().asMilliseconds() > arr) {
				RARRClock.restart();
				gameState.moveX(curMino, 1);
			}

		}
	}
	else {
		if (Rclock.getElapsedTime().asMilliseconds() > das && rightPressed) {
			gameState.arrX(curMino, 1);
			//RclockRestarted = false;
		}
	}
}

void PlayerGame::inputLeft(bool leftPressed, bool rightPressed) {
	//if (rightPressed) return;
	if (rightPressed && LARRClock.getElapsedTime().asMilliseconds() > 0 && leftPressed) {
		Rclock.restart();
	}

	if (leftPressed && LclockRestarted == false) {
		Lclock.restart();
		LclockRestarted = true;
		gameState.moveX(curMino, -1);

	}
	else {
		if (leftPressed == false) LclockRestarted = false;
	}
	if (arr > 0) {
		if (Lclock.getElapsedTime().asMilliseconds() > das && leftPressed) {
			if (LARRClock.getElapsedTime().asMilliseconds() > arr) {
				LARRClock.restart();
				gameState.moveX(curMino, -1);
			}
		}
	}
	else {
		if (Lclock.getElapsedTime().asMilliseconds() > das && leftPressed) {
			gameState.arrX(curMino, -1);
			//LclockRestarted = false;
		}
	}
}

void PlayerGame::inputDown() {
	if (sdf == 0) {
		gameState.hardDropWithoutPaste(curMino);
	}
	else {
		if (SDFClock.getElapsedTime().asMilliseconds() > sdf) {
			SDFClock.restart();
			gameState.softDrop(curMino);
		}
	}
}

int PlayerGame::inputGeneral(int keyCode) {
	// hard drop
	if (keyCode == Globals::CONTROLS["hard_drop"]) {
		int mino = curMino.minoIndex;
		gameState.hardDrop(curMino);
		curMino.setPolyomino(nextList.front());
		nextList.erase(nextList.begin());
		if (nextList.size() < Globals::PREVIEWS * 2) GameState::pushOntoNextlist(nextList);
		gameState.clearLines();
		
		if(Globals::POLY_SIZE > 11) std::thread{ Globals::addPolyominoToPool }.detach();
	}

	if (keyCode == Globals::CONTROLS["hold"]) {
		gameState.performHold(gameState, curMino, nextList);
	}
	if (keyCode == Globals::CONTROLS["rot_cw"]) {
		gameState.rotate(curMino, 1);
	}
	if (keyCode == Globals::CONTROLS["rot_ccw"]) {
		gameState.rotate(curMino, -1);
	}
	if (keyCode == Globals::CONTROLS["rot_180"]) {
		gameState.rotate(curMino, 2);
	}
	if (keyCode == Globals::CONTROLS["restart"]) {
		gameState.resetMatrix();
	}



	return 0;
}

