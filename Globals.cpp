#include "Globals.h"

#include <string>
#include <iostream>

#include <fstream>
#include <sstream>


std::vector<std::vector<Point>> Globals::polyominoes;

void Globals::InitVars() {

	std::string file = std::string{ "Polyominoes/" } + std::string{ "Polyominoes Size " } + std::to_string(POLY_SIZE) + std::string{ ".txt" };

	std::ifstream input{ file };
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


	input.close();
}
