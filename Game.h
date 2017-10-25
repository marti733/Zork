/*
 * Game.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include <vector>
#include <map>
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
	bool status;
	map<string, Room*> rooms;
	map<string, Container*> containers;
	map<string, Creature*> creatures;
	map<string, Item*> items;

public:
	Game(int i) : status(true) {}
	virtual ~Game() {}

	bool getStatus();
	void setStatus(bool);
	void runGame(string);
	bool getSetup(string);
	bool checkTriggers();
	void executeCommand(string);
	void parseXML(xml_node<> *);
};



#endif /* GAME_H_ */
