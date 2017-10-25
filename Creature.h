/*
 * Creature.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef CREATURE_H_
#define CREATURE_H_

class Creature {
public:
	string name;
	string vulnerability;

	Creature(xml_node<char>* name);
	virtual ~Creature() {}
};



#endif /* CREATURE_H_ */
