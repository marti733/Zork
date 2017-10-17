/*
 * main.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */

#include <iostream>
#include <fstream>
#include "Game.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

int main(int arc, char ** argv) {

	std::ifstream file("sample.xml");

	if(!(file.is_open())){
		std::cout << "Cannot open file!" << std::endl;
		return EXIT_FAILURE;
 	}

	Game* g = new Game(1);

	std::cout << g->getStatus() << std::endl;

	return EXIT_SUCCESS;
}



