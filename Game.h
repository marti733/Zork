/*
 * Game.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>

using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
	bool status;

public:
	Game(int i) : status(true) {}
	virtual ~Game() {}

	bool getStatus();
	void setStatus(bool);
	void runGame(string);
	bool getSetup(string);
	bool checkTriggers();
	void executeCommand(string);
};



#endif /* GAME_H_ */
