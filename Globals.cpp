#include "Globals.h"

#include <string>
#include <iostream>

#include <fstream>
#include <sstream>

#include <future>

std::vector<std::vector<Point>> Globals::polyominoes;
size_t Globals::POLY_SIZE = 10;
int Globals::WIDTH = 20;
int Globals::HEIGHT = 40;
int Globals::YMARGIN = HEIGHT/2;
int Globals::DAS = 133;
int Globals::ARR = 10;
int Globals::SDF = 5;
int Globals::PREVIEWS = 2;

std::unordered_map<std::string, sf::Keyboard::Key> Globals::ALL_KEYS;
std::unordered_map<std::string, sf::Keyboard::Key> Globals::CONTROLS;

void Globals::InitVars() {
	InitAllKeys();

	{
		std::string file = std::string{ "Polyominoes/" } + std::string{ "Polyominoes Size " } + std::to_string(POLY_SIZE) + std::string{ ".txt" };

		std::ifstream input{ file };
		if (input.good()) {
			for (std::string line; std::getline(input, line); ) {

				polyominoes.push_back(std::vector<Point>{});
				polyominoes.at(polyominoes.size() - 1).reserve(POLY_SIZE);

				std::vector<Point> temp{}; temp.reserve(POLY_SIZE);
				int xTotal = 0;
				int yTotal = 0;
				for (std::string::size_type i = 0; i < line.size(); ++i) {
					char c = line[i];
					if (c == '(') {
						int x = line[i + 1] - '0';
						int y = line[i + 4] - '0';
						xTotal += x; yTotal += y;
						temp.push_back(Point{ x, y });
					}
				}
				int avX = xTotal / POLY_SIZE;
				int avY = yTotal / POLY_SIZE;
				for (auto& p : temp) {
					p.x -= avX; p.y -= avY;
				}
				polyominoes.at(polyominoes.size() - 1) = temp;

			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				std::thread{ addPolyominoToPool }.detach();
			}
			// add a few initially so that the bag is guaranteed to have some before it initializes
			for (int i = 0; i < 2; ++i) {
				addPolyominoToPool();
			}

		}
		input.close();
	}

	std::ifstream file("config.ini");
	if (file.is_open()) {
		std::string line;

		while (getline(file, line)) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace),
				line.end());

			if (line[0] == '[' || line.empty())
				continue;

			auto delimiterPos = line.find("=");
			auto name = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);
			std::cout << name << " " << value << '\n';

			if (name == "sdf") SDF = std::stoi(value);
			if (name == "das") DAS = std::stoi(value);
			if (name == "arr") ARR = std::stoi(value);

			if (name == "width") WIDTH = std::stoi(value);
			if (name == "height") HEIGHT = std::stoi(value) * 2;
			if (name == "polyomino_size") POLY_SIZE = std::stoi(value);
			if (name == "previews") PREVIEWS = std::stoi(value);

		}

	}
	else {
		std::cout << "Config file not opened";
	}


	std::cout << '\n';
	std::ifstream controlsFile("controls.ini");
	if (controlsFile.is_open()) {
		std::string line;

		while (getline(controlsFile, line)) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace),
				line.end());

			if (line[0] == '[' || line.empty())
				continue;

			auto delimiterPos = line.find("=");
			auto name = line.substr(0, delimiterPos);
			auto value = line.substr(delimiterPos + 1);
			std::cout << name << " " << value << '\n';

			CONTROLS[name] = ALL_KEYS[value];


		}

	}
	else {
		std::cout << "Controls file not opened";
	}

	YMARGIN = HEIGHT / 2;
}




std::vector<Point> Globals::generateRandomPolyomino() {

	std::vector<Point> polyomino; polyomino.reserve(POLY_SIZE);
	polyomino.push_back({ 0,0 });

	for(int i = 0; i < POLY_SIZE; ++i) {
		Point point{ polyomino[rand() % polyomino.size()] }; // the point to be expanded

		std::vector<Point> checks{
			{point.x - 1, point.y },
			{point.x + 1, point.y },
			{point.x,     point.y - 1 },
			{point.x,     point.y + 1 }
		};


		while (checks.size() > 0) {
			int randCheck = rand() % checks.size();

			for (auto& point : polyomino) {
				// if the polyomino already has this point, then erase it and try the next check
				if (checks[randCheck] == point) {
					checks.erase(checks.begin() + randCheck);
					goto NEXT_CHECK;
				}

			}
			// otherwise, this point is the correct point to be added
			polyomino.push_back(checks[randCheck]);
			goto NEXT_TILE;

		NEXT_CHECK:;
		}
		--i;

	NEXT_TILE:;
	}



	return polyomino;
}

void Globals::InitAllKeys() {

#define INSERT_KEY_MAPPING(identifier) ALL_KEYS.insert({#identifier, sf::Keyboard::identifier })

	INSERT_KEY_MAPPING(Unknown);
	INSERT_KEY_MAPPING(A);
	INSERT_KEY_MAPPING(B);
	INSERT_KEY_MAPPING(C);
	INSERT_KEY_MAPPING(D);
	INSERT_KEY_MAPPING(E);
	INSERT_KEY_MAPPING(F);
	INSERT_KEY_MAPPING(G);
	INSERT_KEY_MAPPING(H);
	INSERT_KEY_MAPPING(I);
	INSERT_KEY_MAPPING(J);
	INSERT_KEY_MAPPING(K);
	INSERT_KEY_MAPPING(L);
	INSERT_KEY_MAPPING(M);
	INSERT_KEY_MAPPING(N);
	INSERT_KEY_MAPPING(O);
	INSERT_KEY_MAPPING(P);
	INSERT_KEY_MAPPING(Q);
	INSERT_KEY_MAPPING(R);
	INSERT_KEY_MAPPING(S);
	INSERT_KEY_MAPPING(T);
	INSERT_KEY_MAPPING(U);
	INSERT_KEY_MAPPING(V);
	INSERT_KEY_MAPPING(W);
	INSERT_KEY_MAPPING(X);
	INSERT_KEY_MAPPING(Y);
	INSERT_KEY_MAPPING(Z);
	INSERT_KEY_MAPPING(Num0);
	INSERT_KEY_MAPPING(Num1);
	INSERT_KEY_MAPPING(Num2);
	INSERT_KEY_MAPPING(Num3);
	INSERT_KEY_MAPPING(Num4);
	INSERT_KEY_MAPPING(Num5);
	INSERT_KEY_MAPPING(Num6);
	INSERT_KEY_MAPPING(Num7);
	INSERT_KEY_MAPPING(Num8);
	INSERT_KEY_MAPPING(Num9);
	INSERT_KEY_MAPPING(Escape);
	INSERT_KEY_MAPPING(LControl);
	INSERT_KEY_MAPPING(LShift);
	INSERT_KEY_MAPPING(LAlt);
	INSERT_KEY_MAPPING(LSystem);
	INSERT_KEY_MAPPING(RControl);
	INSERT_KEY_MAPPING(RShift);
	INSERT_KEY_MAPPING(RAlt);
	INSERT_KEY_MAPPING(RSystem);
	INSERT_KEY_MAPPING(Menu);
	INSERT_KEY_MAPPING(LBracket);
	INSERT_KEY_MAPPING(RBracket);
	INSERT_KEY_MAPPING(SemiColon);
	INSERT_KEY_MAPPING(Comma);
	INSERT_KEY_MAPPING(Period);
	INSERT_KEY_MAPPING(Quote);
	INSERT_KEY_MAPPING(Slash);
	INSERT_KEY_MAPPING(BackSlash);
	INSERT_KEY_MAPPING(Tilde);
	INSERT_KEY_MAPPING(Equal);
	INSERT_KEY_MAPPING(Dash);
	INSERT_KEY_MAPPING(Space);
	INSERT_KEY_MAPPING(Return);
	INSERT_KEY_MAPPING(BackSpace);
	INSERT_KEY_MAPPING(Tab);
	INSERT_KEY_MAPPING(PageUp);
	INSERT_KEY_MAPPING(PageDown);
	INSERT_KEY_MAPPING(End);
	INSERT_KEY_MAPPING(Home);
	INSERT_KEY_MAPPING(Insert);
	INSERT_KEY_MAPPING(Delete);
	INSERT_KEY_MAPPING(Add);
	INSERT_KEY_MAPPING(Subtract);
	INSERT_KEY_MAPPING(Multiply);
	INSERT_KEY_MAPPING(Divide);
	INSERT_KEY_MAPPING(Left);
	INSERT_KEY_MAPPING(Right);
	INSERT_KEY_MAPPING(Up);
	INSERT_KEY_MAPPING(Down);
	INSERT_KEY_MAPPING(Numpad0);
	INSERT_KEY_MAPPING(Numpad1);
	INSERT_KEY_MAPPING(Numpad2);
	INSERT_KEY_MAPPING(Numpad3);
	INSERT_KEY_MAPPING(Numpad4);
	INSERT_KEY_MAPPING(Numpad5);
	INSERT_KEY_MAPPING(Numpad6);
	INSERT_KEY_MAPPING(Numpad7);
	INSERT_KEY_MAPPING(Numpad8);
	INSERT_KEY_MAPPING(Numpad9);
	INSERT_KEY_MAPPING(F1);
	INSERT_KEY_MAPPING(F2);
	INSERT_KEY_MAPPING(F3);
	INSERT_KEY_MAPPING(F4);
	INSERT_KEY_MAPPING(F5);
	INSERT_KEY_MAPPING(F6);
	INSERT_KEY_MAPPING(F7);
	INSERT_KEY_MAPPING(F8);
	INSERT_KEY_MAPPING(F9);
	INSERT_KEY_MAPPING(F10);
	INSERT_KEY_MAPPING(F11);
	INSERT_KEY_MAPPING(F12);
	INSERT_KEY_MAPPING(F13);
	INSERT_KEY_MAPPING(F14);
	INSERT_KEY_MAPPING(F15);
	INSERT_KEY_MAPPING(Pause);

#undef INSERT_KEY_MAPPING
}