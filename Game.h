/*
 * Game.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
	std::string status;
public:
	Game(int i) : status("Success") {}
	virtual ~Game() {}

	std::string getStatus();
};



#endif /* GAME_H_ */
