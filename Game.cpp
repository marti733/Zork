/*
 * Game.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: cheyenne
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <istream>
#include <string>
#include <sstream>
#include "Game.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

/* Returns the status of the game
 *
 * Parameter(s): VOID
 * Return: Status of the game */
bool Game::getStatus() {
		return status;
}

/*
 * Sets / updates the status of the game
 * Parameter(s): Status value to set
 * Return: void */
void Game::setStatus(bool n) {
	if (n)
		this->status = true;
	else
		this->status = false;
}

/* Setups the structure of the game by reading in the xml file and extracting the data
 * into separate elements and checks for validity of data
 *
 * Parameter(s): xml filename
 * Return: status of the game */
bool Game::getSetup(string filename) {
	std::ifstream file("sample.xml");

	if(!(file.is_open())){
		std::cout << "Cannot open file!" << std::endl;
		setStatus(false);
		return false;
 	}

	xml_document<> doc;
	xml_node<> * root;

	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	root = doc.first_node();

	if (root == nullptr)
		setStatus(false);
	else {
		setStatus(true);
		parseXML(root->first_node());
	}

	return getStatus();
}


/* Starts game interface and handles input and output after initial setup
 *
 * Parameter(s): xml filename
 * Return: void */
void Game::runGame(string filename) {
	this->getSetup(filename);

	string command;
	this->location = "Entrance";
	cout << rooms[location]->description << endl;

	//Run game until exit condition or error occurs
	while(this->status){
		std::cout << "> ";
		getline(cin, command);

		bool trigger_found = checkTriggers(command);

		if (!trigger_found){

			executeCommand(command);
		}
	}
}

/* Check all object triggers and output appropriate action to override input or accept user input
 *
 * Parameter(s): void
 * Return: Override instruction - true for override false for accepting input */
bool Game::checkTriggers(string command ){
	bool result = false;

	//Check current room triggers
	Room * c_room = rooms[location];

	if(!(c_room->triggers.empty())){
		result = executeTrigger(c_room->triggers, command);

		if(result)
			return result;
	}

	//Check map item triggers
	for (map<string, Item*>::iterator it = items.begin(); it != items.end(); it++){

		//Check triggers exist
		if(!(it->second->triggers.empty()))
			result = executeTrigger(it->second->triggers, command);

		if(result)
			return result;
	}

	//Check map container triggers
	for (map<string, Container*>::iterator it = containers.begin(); it != containers.end(); it++){

		if(!(it->second->triggers.empty()))
				result = executeTrigger(it->second->triggers, command);
		if(result)
			return result;
	}

	//Check map creature triggers
	for (map<string, Creature*>::iterator it = creatures.begin(); it != creatures.end(); it++){

		if(!(it->second->triggers.empty()))
				result = executeTrigger(it->second->triggers, command);
		if(result)
			return result;
	}

	//Check item triggers in current room
	for (map<string, Item*>::iterator it = c_room->items.begin(); it != c_room->items.end(); it++){

		result = executeTrigger(it->second->triggers, command);

		if(result)
			return result;
	}


	//Check container triggers current room
	for (map<string, Container*>::iterator it = c_room->containers.begin(); it != c_room->containers.end(); it++){

		result = executeTrigger(it->second->triggers, command);

		if(result)
			return result;
	}

	//Check creature triggers current room
	for (map<string, Creature*>::iterator it = c_room->creatures.begin(); it != c_room->creatures.end(); it++){

		result = executeTrigger(it->second->triggers, command);

		if(result)
			return result;
	}

	return false;
}

bool Game::executeTrigger(vector<Trigger*> triggers, string command){
	Trigger* c_trigger;
	bool result;

	for(int i = 0; i < triggers.size(); i++){
		c_trigger = triggers[i];

		//Check for command
		if(command == c_trigger->command){
			//Check not done
			if(c_trigger->type != "done"){
				result = checkCondition(c_trigger->conditions);

				if(result){
					if(c_trigger->type == "single"){
						c_trigger->type = "done";
						cout << "done" << endl;
					}
					if(c_trigger->print != "")
						cout << c_trigger->print << endl;

					if(!(c_trigger->action.empty())){
						for(int j = 0; j < c_trigger->action.size(); j++){
							executeCommand(c_trigger->action[j]);
						}
					}
					return result;
				}
			}
		}
	}

	return false;
}

/* If there is no trigger override, execute user input command. Split command into words for
 * function calls.
 *
 * Parameter(s): user input command
 * Return: void */
void Game::executeCommand(string command) {

	stringstream strstr(command);

	// use stream iterators to copy the stream to the vector as whitespace separated strings
	istream_iterator<string> it(strstr);
	istream_iterator<string> end;
	vector<string> results(it, end);


	if(command.find("attack") != string::npos) {
		attackCreature(command);
	}
	else if (command.find("turn on") != string::npos){
		turnOn(command);
	}
	else if (command.find("put") != string::npos){
		putItem(command);
	}
	else if (command.find("drop") != string::npos){
		dropItem(command);
	}
	else if (command.find("read") != string::npos){
		readItem(command);
	}
	else if (command.find("open exit") != string::npos){
		if (isExit())
			return;
	}
	else if (command.find("open") != string::npos){
		openObject(command);
	}
	else if (command.find("take") != string::npos){
		takeItem(command);
	}
	else if (command == "i"){
		getInventory();
	}
	else if ((command == "n") || command == "north"){
		navigateDirection("n");
	}
	else if (command == "s" || command == "south"){
		navigateDirection("s");
	}
	else if (command == "e" || command == "east"){
		navigateDirection("e");
	}
	else if (command == "w" || command == "west"){
		navigateDirection("w");
	}
	else if (command.find("Add") != string::npos){
		addObject(command);
	}
	else if (command.find("Delete") != string::npos){
		deleteObject(command);
	}
	else if (command.find("Update") != string::npos){
		updateObject(command);
	}
	else if (command.find("Game Over") != string::npos){
		std::cout << "Victory!" << std::endl;
	}
	//FOR TESTING REMOVE BEFORE DEMO
	else if (command.find("q") != string::npos || command.find("quit") != string::npos){
		string response;
		std::cout << "Are you sure you want to quit?" << endl << ">";
		getline(cin, response);

		if(response == "y" || response == "Y" || response == "yes"){
			this->status = false;
			cout << "Goodbye" << endl;
		}
	}
	else {
		std::cout << "That command doesn't exist." << std::endl;
	}

}

/* Takes in xml data structure and adds elements to the game
 *
 * Parameter(s): xml filename
 * Return: status of the game */
void Game::parseXML(xml_node<> * root){
	while(root != nullptr){
		if(string((root->name())) == "room") {
			Room* room = new Room(root->first_node());
			rooms[room->name] = room;
		}
		else if(string((root->name())) == "item") {
			Item* item = new Item(root->first_node());
			items[item->name] = item;
		}
		else if(string((root->name())) == "container") {
			Container* container = new Container(root->first_node());
			containers[container->name] = container;
		}
		else if(string((root->name())) == "creature") {
			Creature* creature = new Creature(root->first_node());
			creatures[creature->name] = creature;
		} else {
			cout << "Error: Not a supported object" << endl;
		}

		root = root->next_sibling();
	}
}

/* Movement commands to put the player in a different room. If the indicated direction
 * leads to a new room, the description of the new room is be printed to the screen.
 * Otherwise print “Can’t go that way.”
 *
 * Parameter(s): direction command
 * Return: void */
void Game::navigateDirection(string direction){
	Room* c_room = rooms[this->location];
	string d;

	if(direction == "n") {
		d = "north";
	}
	else if (direction == "s") {
		d = "south";
	}
	else if (direction == "e") {
		d = "east";
	}
	else if (direction == "w"){
		d = "west";
	}

	map<string, Border*>::iterator it;

	it = c_room->borders.find(d);
	if(it == c_room->borders.end())
		cout << "Can’t go that way." << endl;
	else {
		this->location = it->second->name;
		cout << rooms[location]->description << endl;
	}

}

/* Lists all items in the player’s inventory with each item separated by commas, if the
 * player has more than one item. If there are no items in the player's inventory print
 * "Inventory: empty"
 *
 * Parameter(s): void
 * Return: void */
void Game::getInventory(){
	if(inventory.empty()){
		cout << "Inventory: empty" << std::endl;
	}
	else {
		cout << "Your inventory contains: ";
		for (map<string, Item*>::iterator it = inventory.begin(); it != inventory.end(); it++)
		{
			if (it == inventory.begin())
				cout << it->second->name;
			else
				cout << ", "<< it->second->name;
		}
		cout << "." << std::endl;
	}
}

/* Changes item ownership from room or container to inventory. If successful
 * print “Item (item) added to inventory”
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::takeItem(string command){
	vector<string> com = splitCommand(command);
	if(com.size() < 2) {
		cout << "To take an item, the command must be in the form of 'take (item)'." << endl;
		return;
	}
	Room * c_room = rooms.find(location)->second;
	string item = com[1];

	//Check if item is already in inventory
	if(inventory.find(item) != inventory.end()){
		cout << "The " << item << " is already in your inventory." << endl;
	}
	else{
		// Check if item is in the game
		if (items.find(item) != items.end()){
			inventory[item] = items[item];
			items.erase(item);
			cout << "The " <<  item << " was taken from the room and is in your inventory." << endl;
		}
		else{
			//Check if item is in the current room
			if(c_room->items.find(item) != c_room->items.end()) {
				inventory[item] = c_room->items[item];
				c_room->items.erase(item);
				cout << "The " <<  item << " was taken from " << c_room->name << " and added to inventory." <<endl;
			}
			else {
				//Check open containers
				for(map<string,Container*>::iterator it = c_room->containers.begin(); it!= c_room->containers.end(); it++) {
					Container * c_container = it->second;
					if(c_container->status == "open") {
						//Find item in open container
						if(c_container->items.find(item) != c_container->items.end()) {
							inventory[item] = c_container->items[item];
							c_container->items.erase(item);
							cout << "The " <<  item << " was taken from " << c_container->name << " and put in your inventory." << endl;
							return;
						}
					}
				}

				cout << "The " <<  item << " does not exist, try opening a container." << endl;
			}
		}
	}
}

/* Adds the item to the containers inventory and and prints “Item (item) added to (container).”
 * If the object is not in the players inventory indicate that by printing an appropriate
 * message.
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::putItem(string command){
	vector<string> com = splitCommand(command);
	if(com.size() < 4) {
		cout << "Error: put command must be in the format of 'put (item) in (container).'" << endl;
		return;
	}
	string item = com[1];
	string container = com[3];

	if(inventory.find(item) == inventory.end()){
		cout << "The " << item << " is not in your inventory" << endl;
	}
	else{
		if (containers.find(container) == containers.end()){
			if(rooms[location]->containers.find(container) == rooms[location]->containers.end()){
				cout << "The " << container << " does not exist here." << endl;
				return;
			}
			else {
				if (rooms[location]->containers[container]->status == "open") {
					rooms[location]->containers[container]->items[item] = inventory[item];
					inventory.erase(item);
					cout << "The " << item << " was put in the " << container << endl;
				}
				else {
					cout << "The " << container << " is not open" << endl;
				}
			}
		}
		else {
			if (containers[container]->status == "open") {
				containers[container]->items[item] = inventory[item];
				inventory.erase(item);
				cout << "The " << item << " was put in the " << container << endl;
			}
			else {
				cout << "The " << container << " is not open" << endl;
			}
		}
	}


}

/* prints contents of container in format “(container) contains (item), (item), …”
 * and makes those items available to pick up. If empty, you should output "(container)
 * is empty."
 *
 * Parameter(s): container to open
 * Return: void */
void Game::openObject(string command){
	vector<string> com = splitCommand(command);
	Room * c_room = rooms[location];
	if(com.size() < 2) {
		cout << "To open a container, the command must be in the form of 'open (container)'." << endl;
		return;
	}

	string cont = com[1];
	if(containers.find(cont) != containers.end()){
		if(containers[cont]->status == "locked"){
			cout << cont << " is locked." << endl;
		}
		else {
			containers[cont]->status = "open";
			cout << cont << " contains: ";
			for (map<string, Item*>::iterator it = containers[cont]->items.begin(); it != containers[cont]->items.end(); it++)
			{
				if (it == containers[cont]->items.begin())
					cout << it->second->name;
				else
					cout << ", "<< it->second->name;
			}
			cout << "." << std::endl;
		}
	}
	else if (c_room->containers.find(cont) != c_room->containers.end()){
		if (c_room->containers[cont]->status == "locked"){
			cout << cont << " is locked." << endl;
		}
		else {
			c_room->containers[cont]->status = "open";
			cout << cont << " contains: ";
			for (map<string, Item*>::iterator it = c_room->containers[cont]->items.begin(); it != c_room->containers[cont]->items.end(); it++)
			{
				if (it == c_room->containers[cont]->items.begin())
					cout << it->second->name;
				else
					cout << ", "<< it->second->name;
			}
			cout << "." << std::endl;
		}
	}
	else {
		cout << cont << " does not exist or it is not a container." << endl;
	}



}

/* If the room is of type exit prints “Game Over” and gracefully ends the program.
 *
 * Parameter(s): void
 * Return: If exit is found */
bool Game::isExit(){
	Room * current_room = rooms[this->location];

	if(current_room->type == "exit"){
		cout << "Game Over" << endl;
		return true;
	}
	else {
		cout << "This is not an exit!" << endl;
	}

	return false;
}

/* Prints whatever is written on an object that the player has, if something is
 * written on the object and prints “Nothing written.” if nothing is written on the
 * object. If the object is not in the players inventory indicate that by printing an
 * appropriate message
 *
 * Parameter(s): item to read
 * Return: void */
void Game::readItem(string command) {
	vector<string> com = splitCommand(command);
	if(com.size() < 2) {
		cout << "Error! The read command should have the following format: 'read (item)'" << endl;
		return;
	}
	string item = com[1];

	if(inventory.find(item) != inventory.end()) {
		if(inventory[item]->writing != "")
			cout << inventory[item]->writing << endl;
		else
			cout << "The " << item << " does not have anything written on it." << endl;
	}
	else {
		cout << "The " << item << " is not in your inventory." << endl;
	}

}

/* Changes item ownership from inventory to present room and prints “(item) dropped.”
 * If the object is not in the players inventory indicate that by printing an appropriate
 * message.
 *
 * Parameter(s): item to drop
 * Return: void */
void Game::dropItem(string command){
	vector<string> com = splitCommand(command);
	Room* c_room = rooms[location];
	if (com.size() < 2) {
		cout << "Error! The drop function command must have the following format: 'drop (item)'" << endl;
		return;
	}

	string item = com[1];
	if (inventory.find(item) != inventory.end()){
		c_room->items[item] = inventory[item];
		inventory.erase(item);
		cout << item << " dropped" << endl;
	}
	else {
		cout << "The " << item << " is not in your inventory." << endl;
	}

}

/* Activates an item if it is in the player’s inventory printing “You activated the (item).” and
 * executing commands in the “turnon” element. If the object is not in the players inventory
 * indicate that by printing an appropriate message.
 *
 * Parameter(s): item to turn on
 * Return: void */
void Game::turnOn(string command){
	vector<string> com = splitCommand(command);
	if (com.size() < 3) {
		cout << "Error! The turn on function command must have the following format: 'turn on (item)'" << endl;
	}

	string item = com[2];
	if(inventory.find(item) == inventory.end()){
		cout << "The " << item << " is not in your inventory." << endl;
		return;
	}

	if (inventory[item]->turnon == nullptr){
		cout << "The " << item << " cannot be turned on." << endl;
		return;
	}

	cout << "You turned on the " << item << endl;
	cout << inventory[item]->turnon->print << endl;
	if (inventory[item]->turnon->action == ""){
		return;
	}
	executeCommand(inventory[item]->turnon->action);

}

/* Prints “You assault the (creature) with the (item).” and executes “attack” elements if item
 * matches creature’s “vulnerability” and existing conditions are met. If the object is not in
 * the players inventory indicate that by printing an appropriate message.
 *
 * Parameter(s): creature and item
 * Return: void */
void Game::attackCreature(string command){
	vector<string> com = splitCommand(command);

	if(com.size() < 4){
		cout << "Error! Attack command should be in the format: 'attack (creature) with (item)'" << endl;
		return;
	}

	string creature = com[1];
	string item = com[3];

	if(inventory.find(item) == inventory.end()){
		cout << "The " << item << " is not in your inventory" << endl;
		return;
	}

	//Creature is in game
	if(creatures.find(creature) != creatures.end()){
		//Find vulnerability
		if(creatures[creature]->vulnerability.find(item) != creatures[creature]->vulnerability.end()) {
			cout << "You assault " << creature << " with " << item << "." << endl;
			bool result = checkCondition(creatures[creature]->attack->conditions);

			//Conditions met
			if (result) {
				for (int i = 0;  i < creatures[creature]->attack->actions.size(); i++){
					executeCommand(creatures[creature]->attack->actions[i]);
				}
			}
			else{
				cout << "The conditions for attack haven't been met" << endl;
			}
		}
		else
			cout << "The attack failed because " << creature << " is not affected by " << item << endl;
	}

	//Creature is in room
	else if(rooms[location]->creatures.find(creature) != rooms[location]->creatures.end()){

	}
	else {
		cout << "The " << creature << " is not here" << endl;
	}
}

/* Creates instance of object with a specific owner (does not work on the player's inventory).
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::addObject(string command) {
	vector<string> com = splitCommand(command);
	Item * itemO = nullptr;
	Container* containerO = nullptr;
	Creature* creatureO = nullptr;

	Room * roomL = nullptr;
	Container* containerL = nullptr;


	string object = com[1];
	string loc = com[3];

	//Look for object as item in game
	if(items.find(object) != items.end()){
		itemO = items[object];
	}

	//Look for location as room in game
	if(rooms.find(loc) != rooms.end()){
		roomL = rooms[loc];
	}

	//Look for object and location as containers in game
	if(containers.find(object) != containers.end()){
		containerO = containers[object];

	}
	if(containers.find(loc) != containers.end()){
		containerL = containers[loc];

	}

	//Look for object as creature in game
	if(creatures.find(object) != creatures.end()) {
		creatureO = creatures[object];
	}

	//Look for item in inventory
	if(inventory.find(object) != inventory.end()) {
		itemO = items[object];
	}

	//Look for item in containers in game
	for (map<string, Container*>::iterator it = containers.begin(); it != containers.end(); it++){
		if (it->second->items.find(object) != it->second->items.end()){
			itemO = it->second->items[object];
		}
	}
	//Look for item in rooms and items in containers in rooms
	for (map<string, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		//Look for items in room
		if(it->second->items.find(object) != it->second->items.end()){
			itemO = it->second->items[object];
		}

		//Look for creature in rooms
		if(it->second->creatures.find(object) != it->second->creatures.end()){
			creatureO = it->second->creatures[object];
		}

		//Look for object and location as container in rooms
		if(it->second->containers.find(object) != it->second->containers.end()){
			containerO = it->second->containers[object];
		}
		if(it->second->containers.find(loc) != it->second->containers.end()){
			containerL = it->second->containers[loc];
		}

		//Look for object as an item in containers in room
		for (map<string, Container*>::iterator iter = it->second->containers.begin(); iter != it->second->containers.end(); iter++){
			if (iter->second->items.find(object) != iter->second->items.end()){
				itemO = iter->second->items[object];
			}
		}
	}

	//Location is a room
	if(roomL != nullptr){
		//Object is item add item to room
		if(itemO != nullptr)
			roomL->items[itemO->name] = itemO;

		//Object is container add container to room
		else if(containerO != nullptr) {
			roomL->containers[containerO->name] = containerO;
		}

		//Object is creature add creature to room
		else if(creatureO != nullptr)
			roomL->creatures[creatureO->name] = creatureO;

		else
			cout << "Error: no " << object << " could be found " << endl;
	}

	//Location is container
	else if(containerL != nullptr){
		//Object is item add item to room
		if(itemO != nullptr)
			containerL->items[itemO->name] = itemO;
		else {
			cout << "Error: no " << object << " could be found" << endl;
		}
	}

	else {
		cout << "Error: location must be a room or container" << endl;
	}
}

/* Removes object references from game, but the item can still be brought back into the game
 * using the 'Add' command. If a room is removed other rooms will have references to the
 * removed room as a 'border' that was removed, but there is no means for adding a room back in.
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::deleteObject(string command){
	vector<string> com = splitCommand(command);

	string object = com[1];

	//Look for items in game
	if(items.find(object) != items.end()){
		items.erase(object);
		return;
	}
	//Look for rooms in game
	if(rooms.find(object) != rooms.end()){
		rooms.erase(object);
		return;
	}
	//Look for containers in game
	if(containers.find(object) != containers.end()){
		containers.erase(object);
		return;
	}
	//Look for creatures in game
	if(creatures.find(object) != creatures.end()) {
		creatures.erase(object);
		return;
	}
	//Look for item in inventory
	if(inventory.find(object) != inventory.end()) {
		inventory.erase(object);
		return;
	}
	//Look for item in containers in game
	for (map<string, Container*>::iterator it = containers.begin(); it != containers.end(); it++){
		if (it->second->items.find(object) != it->second->items.end()){
			it->second->items.erase(object);
			return;
		}
	}
	//Look for item in rooms and items in containers in rooms
	for (map<string, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		//Look for items in room
		if(it->second->items.find(object) != it->second->items.end()){
			it->second->items.erase(object);
			return;
		}

		//Look for creature in rooms
		if(it->second->creatures.find(object) != it->second->creatures.end()){
			it->second->creatures.erase(object);
			return;
		}

		//Look for container in rooms
		if(it->second->containers.find(object) != it->second->containers.end()){
			it->second->containers.erase(object);
			return;
		}


		//Look for item in containers in room
		for (map<string, Container*>::iterator iter = it->second->containers.begin(); iter != it->second->containers.end(); iter++){
			if (iter->second->items.find(object) != iter->second->items.end()){
				iter->second->items.erase(object);
				return;
			}
		}
	}
	cout << "Error: object not found. Could not delete." << endl;
}

/* Creates new status for object that can be checked by triggers
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::updateObject(string command){
	vector<string> com = splitCommand(command);

	string object = com[1];
	string stat = com[3];

	//Look for items in game
	if(items.find(object) != items.end()){
		items[object]->status = stat;
		checkTriggers("");
		return;
	}
	//Look for rooms in game
	if(rooms.find(object) != rooms.end()){
		rooms[object]->status = stat;
		checkTriggers("");
		return;
	}
	//Look for containers in game
	if(containers.find(object) != containers.end()){
		containers[object]->status = stat;
		checkTriggers("");
		return;
	}
	//Look for creatures in game
	if(creatures.find(object) != creatures.end()) {
		creatures[object]->status = stat;
		checkTriggers("");
		return;
	}
	//Look for item in inventory
	if(inventory.find(object) != inventory.end()) {
		inventory[object]->status = stat;
		checkTriggers("");
		return;
	}
	//Look for item in containers in game
	for (map<string, Container*>::iterator it = containers.begin(); it != containers.end(); it++){
		if (it->second->items.find(object) != it->second->items.end()){
			it->second->items[object]->status = stat;
			checkTriggers("");
			return;
		}
	}
	//Look for item in rooms and items in containers in rooms
	for (map<string, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		//Look for items in room
		if(it->second->items.find(object) != it->second->items.end()){
			it->second->items[object]->status = stat;
			checkTriggers("");
			return;
		}
		//Look for creature in rooms
		if(it->second->creatures.find(object) != it->second->creatures.end()){
			it->second->creatures[object]->status = stat;
			checkTriggers("");
			return;
		}
		//Look for container in rooms
		if(it->second->containers.find(object) != it->second->containers.end()){
			it->second->containers[object]->status = stat;
			checkTriggers("");
			return;
		}
		//Look for item in containers in room
		for (map<string, Container*>::iterator iter = it->second->containers.begin(); iter != it->second->containers.end(); iter++){
			if (iter->second->items.find(object) != iter->second->items.end()){
				iter->second->items[object]->status = stat;
				checkTriggers("");
				return;
			}
		}
	}
	cout << "Error: object not found. No update made." << endl;

}

/* Creates a vector of words from user input command
 *
 * Parameter(s): Command to be parsed
 * Return: Vector of words */
vector<string> Game::splitCommand(string command){
	string buffer;
	stringstream ss(command);

	vector<string> words;

	while (ss >> buffer)
		words.push_back(buffer);

	return words;
}

bool Game::checkCondition(vector<Condition*> conditions){
	Condition* condition;
	bool result = true;

	if(conditions.empty()){
		return true;
	}

	for(int i = 0; i < conditions.size(); i++) {
		condition = conditions[i];

		if (condition != nullptr){

			bool hasH = checkHas(condition);
			char hasO = hasOwner(condition);
			char hasS = hasStatus(condition);

			if(hasH){
				if(!((hasO == 't' || hasO == 'n') && (hasS == 't' || hasS == 'n')))
					result = false;
			}
			else {
				if(hasO == 't' || hasS == 't')
					result = false;
			}
		}
	}

	if(result == true)
		return true;
	return false;
}

bool Game::checkHas(Condition* con){
	if(con->has == "yes" || con->has == "")
		return true;

	return false;
}

char Game::hasOwner(Condition* con){
	if(con->owner == "")
		return 'n';

	string owner = con->owner;
	string object = con->object;

	if(owner == "inventory"){
		if(inventory.find(object) != inventory.end())
			return 't';
		else
			return 'f';
	}

	Container* containerOw;
	Creature* creatureOw;
	Room* roomOw;

	//Look for owner as room in game
	if(rooms.find(owner) != rooms.end()){
		roomOw = rooms[owner];
	}

	//Look for owner as container in game
	if(containers.find(owner) != containers.end()){
		containerOw = containers[owner];
	}

	//Look for owner as creature in game
	if(creatures.find(owner) != creatures.end()) {
		creatureOw = creatures[owner];
	}

	//Look for item in rooms and items in containers in rooms
	for (map<string, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{

		//Look for creature in rooms
		if(it->second->creatures.find(owner) != it->second->creatures.end()){
			creatureOw = it->second->creatures[owner];
		}

		//Look for object as container in rooms
		if(it->second->containers.find(owner) != it->second->containers.end()){
			containerOw = it->second->containers[owner];
		}
	}

	//Find owner type
	if(containerOw != nullptr){
		if(containerOw->items.find(object) != containerOw->items.end())
			return 't';
		else if(containerOw->status == object)
			return 't';
		else
			return 'f';
	}
	else if(roomOw != nullptr){
		if(roomOw->items.find(object) != roomOw->items.end())
			return 't';
		else if (roomOw->containers.find(object) != roomOw->containers.end())
			return 't';
		else if (roomOw->creatures.find(object) != roomOw->creatures.end())
			return 't';
		else if (roomOw->type == object)
			return 't';
		else
			return 'f';
	}
	else if(creatureOw != nullptr){
		if(creatureOw->status == object)
			return 't';
		else if(creatureOw->vulnerability.find(object) != creatureOw->vulnerability.end())
			return 't';
		else
			return 'f';
	}

	return 'f';

}

char Game::hasStatus(Condition* con) {
	if(con->status == "")
		return 'n';

	string object = con->object;
	string stat = con->status;

	//Look for items in game
	if(items.find(object) != items.end()){
		if(items[object]->status == stat)
			return 't';
		else
			return 'f';
	}
	//Look for rooms in game
	if(rooms.find(object) != rooms.end()){
		if(rooms[object]->status == stat)
			return 't';
		else
			return 'f';
	}
	//Look for containers in game
	if(containers.find(object) != containers.end()){
		if(containers[object]->status == stat)
			return 't';
		else
			return 'f';
	}
	//Look for creatures in game
	if(creatures.find(object) != creatures.end()) {
		if(creatures[object]->status == stat)
			return 't';
		else
			return 'f';
	}
	//Look for item in inventory
	if(inventory.find(object) != inventory.end()) {
		if(inventory[object]->status == stat){
			return 't';
		}
		else
			return 'f';
	}
	//Look for item in containers in game
	for (map<string, Container*>::iterator it = containers.begin(); it != containers.end(); it++){
		if (it->second->items.find(object) != it->second->items.end()){
			if(it->second->items[object]->status == stat)
				return 't';
			else
				return 'f';
		}
	}
	//Look for item in rooms and items in containers in rooms
	for (map<string, Room*>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		//Look for items in room
		if(it->second->items.find(object) != it->second->items.end()){
			if(it->second->items[object]->status == stat)
				return 't';
			else
				return 'f';
		}

		//Look for creature in rooms
		if(it->second->creatures.find(object) != it->second->creatures.end()){
			if(it->second->creatures[object]->status == stat)
				return 't';
			else
				return 'f';
		}

		//Look for container in rooms
		if(it->second->containers.find(object) != it->second->containers.end()){
			if(it->second->containers[object]->status == stat)
				return 't';
			else
				return 'f';
		}


		//Look for item in containers in room
		for (map<string, Container*>::iterator iter = it->second->containers.begin(); iter != it->second->containers.end(); iter++){
			if (iter->second->items.find(object) != iter->second->items.end()){
				if(iter->second->items[object]->status == stat)
					return 't';
				else
					return 'f';
			}
		}
	}
	cout << "Error: object not found." << endl;
	return 'f';
}
