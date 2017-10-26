/*
 * Room.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include <iostream>
#include "Room.h"
#include "Border.h"
#include "Trigger.h"
#include <map>
using namespace std;

Room::Room(xml_node<> * root){
	string n;
	string v;
	Border* border;

	this->type = "regular";

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		if(n == "name"){
			this->name = v;
		}
		else if (n == "description"){
			this->description = v;
		}
		else if (n == "status"){
			this->status = v;
		}
		else if (n == "type"){
			this->type = v;
		}
		else if (n == "item"){
			Item* item = new Item(root);
			this->items[item->name] = item;
		}
		else if (n == "trigger"){
			this->triggers = new Trigger(root);
		}
		else if (n == "border"){
			border = new Border(root->first_node());
			this->borders[border->direction] = border;
		}

		root = root->next_sibling();
	}

}



