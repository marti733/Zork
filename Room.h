/*
 * Room.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include <map>
#include "Container.h"
#include "Border.h"
#include "Trigger.h"
#include "Item.h"
#include "Creature.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef ROOM_H_
#define ROOM_H_

class Room{
public:
	string description;
	string name;
	string type;
	string status;
	map<string, Border*> borders;
	map<string, Container*> containers;
	Trigger* triggers;
	map<string, Item*> items;
	map<string, Creature*> creatures;



	Room (xml_node<char>* name);
	virtual ~Room() {}

};



#endif /* ROOM_H_ */
