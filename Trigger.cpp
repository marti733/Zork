/*
 * Trigger.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */

#include "Trigger.h"
#include <iostream>

using namespace std;

Trigger::Trigger(xml_node<>* root){
	string n;
	string v;

	this->type = "single";
	this->command = "";

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		if(n == "command"){
			this->command = v;
		}
		else if (n == "action"){
			action.push_back(v);
		}
		else if (n == "condition"){
			Condition* condition = new Condition(root->first_node());
			conditions.push_back(condition);
		}
		else if (n == "type"){
			this->type = v;
		}
		else if (n == "print"){
			this->print = v;
		}

		root = root->next_sibling();
	}
}



