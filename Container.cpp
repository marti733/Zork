/*
 * Container.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include "Container.h"
#include <iostream>

using namespace std;

Container::Container(xml_node<>* root){
	string n;
	string v;

	this->status = "closed";

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
		else if (n == "accept"){
			this->accepts.push_back(v);
		}
		else if (n == "item" && v == ""){
			Item* item = new Item(root->first_node());
			this->items[item->name] = item;
		}
		else if (n == "item" && v != ""){
			Item* item = new Item(root);
			this->items[item->name] = item;
		}
		else if (n == "trigger"){
			triggers.push_back(new Trigger(root->first_node()));

		}
		else if(n == "container"){
			this->name = n;
			return;
		}

		root = root->next_sibling();
	}
}


