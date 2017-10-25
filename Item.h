/*
 * Item.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include <string>
#include "TurnOn.h"
#include "Trigger.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef ITEM_H_
#define ITEM_H_

class Item{
public:
	string name;
	string status;
	string writing;
	string description;
	TurnOn* turnon;
	Trigger* trigger;

	Item(xml_node<>* node);
	virtual ~Item() {}
};



#endif /* ITEM_H_ */
