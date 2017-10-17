/*
 * Trigger.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <string>
#include <vector>
#include "Condition.h"

using namespace std;

#ifndef TRIGGER_H_
#define TRIGGER_H_

class Trigger {
private:
	vector<Condition> conditions;
	string command;
	string type;
	string print;
public:
	Trigger() {}
	virtual ~Trigger() {}
};



#endif /* TRIGGER_H_ */
