/*
 * Attack.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include "Attack.h"
#include <iostream>

using namespace std;

Attack::Attack(xml_node<>* root){
	string n;
	string v;


	while (root != nullptr){
		n = root->name();
		v = root->value();

		if(n == "print"){
			this->print = v;
		}
		else if (n == "action"){
			this->actions.push_back(v);
		}
		else if(n == "condition"){
			conditions.push_back(new Condition(root->first_node()));
		}

		root = root->next_sibling();
	}

}


