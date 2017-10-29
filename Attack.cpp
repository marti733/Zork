/*
 * Attack.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include "Attack.h"

Attack::Attack(xml_node<>* root){
	string n = root->name();
	string v = root->value();

	if(n == "print"){
		this->print = v;
	}
	else if (n == "action"){
		this->actions.push_back(v);
	}
	else if(n == "condition"){
		conditions.push_back(new Condition(root->first_node()));
	}

}


