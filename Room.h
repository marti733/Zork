/*
 * Room.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include <vector>
#include"Container.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef ROOM_H_
#define ROOM_H_

class Room{
public:
	string description;
	string name;
	vector<Container> containers;

	Room (xml_node<char>* name);
	virtual ~Room() {}
};



#endif /* ROOM_H_ */
