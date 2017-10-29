/*
 * Trigger.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */

#include "Trigger.h"

using namespace std;

Trigger::Trigger(xml_node<>* root){
	string n;
	string v;
	int i = 0;

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		this->type = "permanent";

		if(n == "command"){
			this->name = v;
		}
		else if (n == "action"){
			this->action[i++] = v;
		}
		else if (n == "condition"){
			Condition* condition = new Condition(root->first_node());
			conditions.push_back(condition);
		}
		else if (n == "type"){
			this->type = v;
		}
		else if (n == "name"){
			this->name = v;
		}
		else if (n == "print"){
			this->print = v;
		}


		root = root->next_sibling();
	}
}



