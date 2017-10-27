/*
 * Item.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include <iostream>
#include "Item.h"
using namespace std;

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
			this->turnon = new TurnOn(root->first_node());
		}
		else if (n == "trigger"){
			this->trigger = new Trigger(root);
		}
		else if (n == "writing") {
			this->writing = v;
		}
		else if (n == "item"){
			this->name = v;
			return;
		}

		root = root->next_sibling();
	}
}


