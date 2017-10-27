/*
 * TurnOn.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <string>
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef TURNON_H_
#define TURNON_H_

class TurnOn {
public:
	string print;
	string action;

	TurnOn(xml_node<>* root);
	virtual ~TurnOn() {}
};



#endif /* TURNON_H_ */
