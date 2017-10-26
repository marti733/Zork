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

/* Sets/ updates the status of the game
 *
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
		bool check = checkTriggers();

		std::cout << "> ";
		getline(cin, command);

		if (check)
			executeCommand(command);
	}
}

/* Check all object triggers and output appropriate action to override input or accept user input
 *
 * Parameter(s): void
 * Return: Override instruction - true for override false for accepting input */
bool Game::checkTriggers(){
	bool check = true;

	return check;
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
	else if (command == "n"){
		navigateDirection("n");
	}
	else if (command == "s"){
		navigateDirection("s");
	}
	else if (command == "e"){
		navigateDirection("e");
	}
	else if (command == "w"){
		navigateDirection("w");
	}
	else if (command.find("add") != string::npos){
		addObject(command);
	}
	else if (command.find("delete") != string::npos){
		deleteObject(command);
	}
	else if (command.find("update") != string::npos){
		updateObject(command);
	}
	else if (command.find("game over") != string::npos){
		std::cout << "Victory!" << std::endl;
	}
/*	//FOR TESTING REMOVE BEFORE DEMO
	else if (command.find("q") != string::npos){
		this->status = false;
		std::cout << "Game Over" << std::endl;
	}*/
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
		std::cout << "Inventory: empty" << std::endl;
	}
	else {
		std::cout << "Your inventory contains: ";
		for (map<string, Item*>::iterator it = inventory.begin(); it != inventory.end(); it++)
		{
			if (it == inventory.begin())
				std::cout << it->second->name;
			else
				std::cout << ", "<< it->second->name;
		}
		std::cout << "." << std::endl;
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
		cout << "To take an item, specify the item. For example: take item." << endl;
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
						}
					}
				}

				cout << "The " <<  item << " does not exist, try opening a container." << endl;
			}
		}
	}


}

/* prints contents of container in format “(container) contains (item), (item), …”
 * and makes those items available to pick up. If empty, you should output "(container)
 * is empty."
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::openObject(string command){
	vector<string> com = splitCommand(command);

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
 * Parameter(s): command for parsing
 * Return: void */
void Game::readItem(string command) {
	vector<string> com = splitCommand(command);

}

/* Changes item ownership from inventory to present room and prints “(item) dropped.”
 * If the object is not in the players inventory indicate that by printing an appropriate
 * message.
 *
 * Parameter(s): command for grabbing item name
 * Return: void */
void Game::dropItem(string command){
	vector<string> com = splitCommand(command);
}

/* Adds the item to the containers inventory and and prints “Item (item) added to (container).”
 * If the object is not in the players inventory indicate that by printing an appropriate
 * message.
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::putItem(string command){
	vector<string> com = splitCommand(command);
}

/* Activates an item if it is in the player’s inventory printing “You activate the (item).” and
 * executing commands in the “turnon” element. If the object is not in the players inventory
 * indicate that by printing an appropriate message.
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::turnOn(string command){
	vector<string> com = splitCommand(command);
}

/* Prints “You assault the (creature) with the (item).” and executes “attack” elements if item
 * matches creature’s “vulnerability” and existing conditions are met. If the object is not in
 * the players inventory indicate that by printing an appropriate message.
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::attackCreature(string command){
	vector<string> com = splitCommand(command);
}

/* Creates instance of object with a specific owner (does not work on the player's inventory).
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::addObject(string command) {
	vector<string> com = splitCommand(command);
}

/* Removes object references from game, but the item can still be brought back into the game
 * using the 'Add' command. If a room is removed other rooms will have references to the
 * removed room as a 'border' that was removed, but there is no means for adding a room back in.
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::deleteObject(string command){
	vector<string> com = splitCommand(command);
}

/* Creates new status for object that can be checked by triggers
 *
 * Parameter(s): command for parsing
 * Return: void */
void Game::updateObject(string command){
	vector<string> com = splitCommand(command);
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
