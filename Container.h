/*
 * Container.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include <map>
#include "Item.h"
#include "Trigger.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef CONTAINER_H_
#define CONTAINER_H_

class Container{
public:
	string name;
	string status;
	string accept;
	string description;
	Trigger* trigger;
	map<string, Item*> items;

	Container(xml_node<>*);
	virtual ~Container() {}
};



#endif /* CONTAINER_H_ */
