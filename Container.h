/*
 * Container.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>
#include <vector>
#include "Item.h"

using namespace std;

#ifndef CONTAINER_H_
#define CONTAINER_H_

class Container{
private:
	string name;
	string status;
	string accept;

	vector<Item> items;

public:
	Container () {}
	virtual ~Container() {}
};



#endif /* CONTAINER_H_ */
