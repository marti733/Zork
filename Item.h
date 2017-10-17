/*
 * Item.h
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include <string>

#ifndef ITEM_H_
#define ITEM_H_

class Item : public Container {
private:
	std::string name;
	std::string status;
	std::string writing;

public:
	Item() {}
	virtual ~Item() {}
};



#endif /* ITEM_H_ */
