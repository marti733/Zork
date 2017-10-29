/*
 * Creature.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include "Creature.h"
#include <iostream>

using namespace std;

Creature::Creature(xml_node<>* root){
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
		else if (n == "vulnerability"){
			this->vulnerability[v] = v;
		}
		else if (n == "attack"){
			this->attack = new Attack(root->first_node());
		}
		else if (n == "trigger"){
			triggers.push_back(new Trigger(root->first_node()));
		}
		else if(n == "creature"){
			this->name = v;
			return;
		}


		root = root->next_sibling();
	}
}


