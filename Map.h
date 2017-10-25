/*
 * Map.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <vector>
#include "Room.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"

using namespace std;

#ifndef MAP_H_
#define MAP_H_

class Map {
public:
	vector<Room> rooms;
	vector<Item> items;
	vector<Container> containers;
	vector<Creature> creatures;

};



#endif /* MAP_H_ */
