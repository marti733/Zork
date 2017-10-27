/*
 * Container.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include "Container.h"

Container::Container(xml_node<>* root){
	string n;
	string v;

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		this->status = "open";

		if(n == "name"){
			this->name = v;
		}
		else if (n == "description"){
			this->description = v;
		}
		else if (n == "status"){
			this->status = v;
		}
		else if (n == "accept"){
			this->accept = v;
		}
		else if (n == "item"){
			Item* item = new Item(root);
			this->items[item->name] = item;
		}
		else if (n == "trigger"){
			this->trigger = new Trigger(root);

		}

		root = root->next_sibling();
	}
}


