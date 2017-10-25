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
			this->name = n;
		}
		else if (n == "description"){
			this->description = n;
		}
		else if (n == "status"){
			this->status = n;
		}
		else if (n == "type"){
			this->type = n;
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



