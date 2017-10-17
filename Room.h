/*
 * Room.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include <vector>
#include"Container.h"

using namespace std;

#ifndef ROOM_H_
#define ROOM_H_

class Room : public Map{
private:
	string description;
	string name;

	vector<Container> containers;

public:
	Room () {}
	virtual ~Room() {}
};



#endif /* ROOM_H_ */
