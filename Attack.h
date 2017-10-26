/*
 * Attack.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <vector>
#include <string>
#include "Condition.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef ATTACK_H_
#define ATTACK_H_

class Attack {
public:
	Condition* condition;
	string print;
	string action;

	Attack(xml_node<>*);
	virtual ~Attack() {}
};



#endif /* ATTACK_H_ */
