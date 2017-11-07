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
	string location;
	map<string, Room*> rooms;
	map<string, Container*> containers;
	map<string, Creature*> creatures;
	map<string, Item*> items;
	map<string, Item*> inventory;


public:
	Game(int i) : status(true) {}
	virtual ~Game() {}

	bool getStatus();
	void setStatus(bool);
	void runGame(string);
	bool getSetup(string);
	bool checkTriggers(string);
	bool executeTrigger(vector<Trigger*>, string);
	void executeCommand(string, bool);
	void parseXML(xml_node<> *);
	void navigateDirection(string);
	void getInventory(void);
	void takeItem(string);
	void openObject(string);
	void putItem(string);
	void readItem(string);
	void dropItem(string);
	void turnOn(string);
	void attackCreature(string);
	void addObject(string);
	void deleteObject(string);
	void updateObject(string);
	void loadRoom();
	bool isExit();
	vector<string> splitCommand(string);
	bool checkCondition(vector<Condition *>);
	bool checkHas(Condition*);
	char hasOwner(Condition*);
	char hasStatus(Condition*);
	void setupRoom(string);
};



#endif /* GAME_H_ */
