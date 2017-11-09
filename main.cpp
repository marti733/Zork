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

int main(int argc, char ** argv) {

	/*if (argc < 2) {
		std::cout << "Error expected input format: Zork filename.xml" << std::endl;
		return EXIT_FAILURE;
	}*/

	string file = "samples/triggersample.xml";

	Game* g = new Game(1);
	g->runGame(file);

	return EXIT_SUCCESS;
}



