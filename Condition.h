/*
 * Condition.h
 *
 *  Created on: Oct 17, 2017
 *      Author: cheyenne
 */
#include <string>

using namespace std;

#ifndef CONDITION_H_
#define CONDITION_H_

class Condition{
private:
	string has;
	string owner;
	string object;
	string status;
public:
	Condition() {}
	virtual ~Condition() {}
};



#endif /* CONDITION_H_ */
