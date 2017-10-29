/*
 * Room.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */

#include <iostream>
#include "Room.h"
#include "Border.h"
#include "Trigger.h"
#include "Creature.h"
#include "Container.h"
#include <map>
using namespace std;

Room::Room(xml_node<> * root){
	string n;
	string v;
	Border* border;

	this->type = "regular";

	while(root != nullptr) {
		n = root->name();
		v = root->value();

		if(n == "name"){
			this->name = v;
		}
		else if (n == "description"){
			this->description = v;
		}
		else if (n == "status"){
			this->status = v;
		}
		else if (n == "type"){
			this->type = v;
		}
		else if (n == "item"){
			Item* item = new Item(root);
			this->items[item->name] = item;
		}
		else if (n == "trigger"){
			Trigger* trigger = new Trigger(root->first_node());
			triggers.push_back(trigger);
		}
		else if (n == "border"){
			border = new Border(root->first_node());
			this->borders[border->direction] = border;
		}
		else if (n == "creature" && v == ""){
			Creature* creature = new Creature(root->first_node());
			this->creatures[creature->name] = creature;
		}
		else if(n == "creature"){
			Creature* creature = new Creature(root);
			this->creatures[creature->name] = creature;
		}
		else if (n == "container" && v == "") {
			Container* container = new Container(root->first_node());
			this->containers[container->name] = container;
		}
		else if(n == "container" && v != ""){
			Container* container = new Container(root);
			this->containers[container->name] = container;
		}

		root = root->next_sibling();
	}

}
