/*
 * Item.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include "Item.h"

Item::Item(xml_node<>* root){
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
		else if(n == "turnon"){
			this->turnon = new TurnOn(root);
		}
		else if (n == "trigger"){
			this->trigger = new Trigger(root);
		}

		root = root->next_sibling();
	}
}


