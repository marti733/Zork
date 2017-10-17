/*
 * Creature.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <string>

#ifndef CREATURE_H_
#define CREATURE_H_

class Creature {
private:
	std::string name;
	std::string vulnerability;
public:

	Creature() {}
	virtual ~Creature() {}
};



#endif /* CREATURE_H_ */
