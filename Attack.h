/*
 * Attack.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <vector>
#include <string>
#include "Condition.h"

using namespace std;

#ifndef ATTACK_H_
#define ATTACK_H_

class Attack {
private:
	vector<Condition> conditions;
	string print;
	string action;
public:
	Attack() {}
	virtual ~Attack() {}
};



#endif /* ATTACK_H_ */
