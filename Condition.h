/*
 * Condition.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <string>
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

#ifndef CONDITION_H_
#define CONDITION_H_

class Condition{
public:
	string owner;
	string status;
	string object;
	string has;

	Condition(xml_node<>*);
	virtual ~Condition() {}
};



#endif /* CONDITION_H_ */
