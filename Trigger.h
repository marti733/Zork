/*
 * Trigger.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <string>
#include <map>
#include <vector>
#include "Condition.h"
#include "rapidxml.hpp"

using namespace rapidxml;

using namespace std;

#ifndef TRIGGER_H_
#define TRIGGER_H_

class Trigger {
public:
	vector<Condition*> conditions;
	string command;
	string type;
	string print;
	string name;
	vector<string> action;

	Trigger(xml_node<char>* name);
	virtual ~Trigger() {}
};



#endif /* TRIGGER_H_ */
