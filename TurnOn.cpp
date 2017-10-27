/*
 * TurnOn.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <iostream>
#include "TurnOn.h"

using namespace std;

TurnOn::TurnOn(xml_node<>* root){
	string n;
	string v;

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		if(n == "action"){
			this->action = v;
		}
		else if (n == "print"){
			this->print = v;
		}

		root = root->next_sibling();
	}


}


