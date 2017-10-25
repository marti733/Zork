/*
 * Border.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */

#include "Border.h"

Border::Border(xml_node<>* node){
	string n = node->name();
	string v = node->value();

	if(n == "name"){
		this->name = v;
	}
	else if (n == "direction"){
		this->direction = v;
	}
}


