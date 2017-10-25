/*
 * Item.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include <string>
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

	Item(xml_node<char>* name);
	virtual ~Item() {}
};



#endif /* ITEM_H_ */
