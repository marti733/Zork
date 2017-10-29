/*
 * Condition.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include "Condition.h"
#include <iostream>

using namespace std;

Condition::Condition(xml_node<>* root){
	string n;
	string v;

	this->owner = "";
	this->status = "";


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
		else if(n == "object"){
			this->object = v;
		}

		root = root->next_sibling();
	}
}


