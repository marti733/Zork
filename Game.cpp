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
#include "Game.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

bool Game::getStatus() {
		return status;
}

void Game::setStatus(bool n) {
	if (n)
		this->status = true;
	else
		this->status = false;
}

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
		parseXML(root);
	}

	return getStatus();
}



void Game::runGame(string filename) {
	this->getSetup(filename);

	string command;
	//Run game until exit condition or error occurs
	while(this->status){
		bool check = checkTriggers();

		std::cout << "> ";
		getline(cin, command);

		if (check)
			executeCommand(command);
	}
}

bool Game::checkTriggers(){
	bool check = true;

	return check;
}

void Game::executeCommand(string command) {

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
		isExit();
	}
	else if (command.find("open") != string::npos){
		openObject(command);
	}
	else if (command.find("take") != string::npos){
		takeItem(command);
	}
	else if (command.find("i") != string::npos){
		getInventory();
	}
	else if (command.find("n") != string::npos){
		navigateDirection("n");
	}
	else if (command.find("s") != string::npos){
		navigateDirection("s");
	}
	else if (command.find("e") != string::npos){
		navigateDirection("e");
	}
	else if (command.find("w") != string::npos){
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
	//FOR TESTING REMOVE BEFORE DEMO
	else if (command.find("q") != string::npos){
		this->status = false;
		std::cout << "Game Over" << std::endl;
	}
	else {
		std::cout << "That command doesn't exist." << std::endl;
	}

}

//Read in xml data structure and add elements to the current room
void Game::parseXML(xml_node<> * root){
	while(root != nullptr){
		if(string((root->name())) == string("room")) {
			Room* room = new Room(root->first_node());
			rooms[room->name] = room;
		}
		else if(string((root->name())) == string("item")) {
			Item* item = new Item(root->first_node());
			items[item->name] = item;
		}
		else if(string((root->name())) == string("container")) {
			Container* container = new Container(root->first_node());
			containers[container->name] = container;
		}
		else if(string((root->name())) == string("creature")) {
			Creature* creature = new Creature(root->first_node());
			creatures[creature->name] = creature;
		} else {
			std::cout << "Error: Command object not recognized." << std::endl;
		}

		root = root->next_sibling();
	}
}

void Game::navigateDirection(string direction){

}

void Game::getInventory(){

}

void Game::takeItem(string command){

}

void Game::openObject(string command){

}

void Game::isExit(){

}

void Game::readItem(string command) {

}

void Game::dropItem(string command){

}

void Game::putItem(string command){

}

void Game::turnOn(string command){

}

void Game::attackCreature(string command){

}

void Game::addObject(string command) {

}

void Game::deleteObject(string command){

}

void Game::updateObject(string command){

}







