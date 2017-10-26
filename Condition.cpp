/*
 * Condition.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include "Condition.h"

Condition::Condition(xml_node<>* root){
	string n;
	string v;

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		if(n == "owner"){
			this->owner = v;
		}
		else if (n == "status"){
			this->status = v;
		}
		else if(n == "has"){
			this->has = v;
		}
	}
}


