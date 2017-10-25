/*
 * Creature.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include "Attack.h"
#include "Trigger.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef CREATURE_H_
#define CREATURE_H_

class Creature {
public:
	string name;
	string status;
	string description;
	Attack* attack;
	string vulnerability;
	Trigger* trigger;

	Creature(xml_node<>*);
	virtual ~Creature() {}
};



#endif /* CREATURE_H_ */
