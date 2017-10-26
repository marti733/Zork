/*
 * Border.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <iostream>
#include "Border.h"

Border::Border(xml_node<>* root){
	string n;
	string v;

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		if(n == "name"){
			this->name = v;
		}
		else if (n == "direction"){
			this->direction = v;
		}

		root = root->next_sibling();
	}
}


