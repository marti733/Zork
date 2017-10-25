/*
 * Room.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include "Room.h"

Room::Room(xml_node<> * root){
	string n;
	string v;

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
			Trigger* trigger = new Trigger(root);
			this->triggers[trigger->name] = trigger;
		}
		else if (n == "border"){
			this->border = new Border(root);
		}

		root = root->next_sibling();
	}
}



