#include "GameWorld.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include <list>
#include <iostream>
using namespace std;

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::initGameWorld() {

	Item* rock = new Item("rock", "A simple rock", false, false, nullptr);
	listOfItems.push_back(rock);
	Room* main = new Room("mainRoom", "This is the main room there's nothing here save for yourself.", false);
	main->listOfItems.push_back(rock);
	listOfRooms.push_back(main);
	player->actualRoom = main;
}

void GameWorld::setPlayer(Player *p) {
	player = p;
}


void GameWorld::processInput(string input) {
	cout << "Processing input: " << input << endl;
	if (!input.empty()) {
		vector<string> parameters;
		getParameters(input, &parameters);
		for (int i = 0; i < (int) parameters.size(); ++i) cout << parameters[i] << endl;
		if (parameters.size() >= 1) {
			string command = parameters[0];
			if (command == "LOOK") {
				if (parameters.size()-1 > 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else LookAt(parameters[1]);
			}
			else if (command == "USE") {
				if (parameters.size()-1 != 3) printNumberArgumentsError(3, ((int)parameters.size()) - 1);
				else UseItem(parameters[1], parameters[3]);
			}
			else if (command == "NORTH" || command == "SOUTH" || command == "EAST" || command == "WEST") {
				if (parameters.size()-1 != 0) printNumberArgumentsError(0, ((int)parameters.size()) - 1);
				else MoveToDirection(parameters[0]);
			}
			else if (command == "OPEN") {
				if (parameters.size()-1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else Open(parameters[1]);
			}
			else if (command == "TAKE") {
				if (parameters.size()-1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else Take(parameters[1]);
			}
			else if (command == "DROP") {
				if (parameters.size()-1 > 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else Drop(parameters[1]);
			}
			else {
				cout << "Command not recognized" << endl;
			}
		}
		else cout << "Not enough arguments" << endl;
	}
}

void GameWorld::getParameters(string input, vector<string> *params) {
	string parameter;
	for (int i = 0; i < (int)input.size(); ++i) {
		if (i == input.size() - 1) {
			parameter.push_back(input[i]);
			params->push_back(parameter);
			parameter.clear();
		}
		else if (input[i] != ' ' ) {
			parameter.push_back(input[i]);
		}

		else {
			params->push_back(parameter);
			parameter.clear();
		}
	}

} 

Room* GameWorld::fetchRoomByName(string name) {
	for (Room* it : listOfRooms) {
		if ( it->entityName == name) {
			return it;
		}
	}
	return nullptr;
}

void GameWorld::lookTarget(string name) {
	list<Item*> *roomItems = &player->actualRoom->listOfItems;
	bool found = false;
	if (name == "me" || name == "myself") {
		cout << player->entityDescription << endl;
		found = true;
	}
	else if (!found && name == player->actualRoom->entityName) {
		cout << player->actualRoom->entityDescription << endl;
		found = true;
	}
	else {
		if (!(*roomItems).empty()) {
			for (list<Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end() && !found; ++it) {
				if ((*it)->entityName == name) {
					cout << (*it)->entityDescription << endl;
					found = true;
				}
			}
		}
	}
	if (!found) cout << "I cannot find " << name << " to look at."<<endl;
}

void GameWorld::printNumberArgumentsError(int argumentsNeeded, int argumentsProvided) {
	cout << "Error number of arguments invalid, arguments needed: " << argumentsNeeded << " arguments provided: " << argumentsProvided << endl;
}

void GameWorld::MoveToDirection(std::string direction) {
	int roomIndex;
	if (direction == "NORTH") roomIndex = NORTH;
	if (direction == "SOUTH") roomIndex = SOUTH;
	if (direction == "EAST") roomIndex = EAST;
	if (direction == "WEST") roomIndex = WEST;
	if (direction == "UP") roomIndex = UP;
	if (direction == "DOWN") roomIndex = DOWN;
	string roomName = player->actualRoom->getExit(roomIndex);
	if (!roomName.empty()) {
		cout << "Moving to direction: " + roomName << endl;
		player->actualRoom = fetchRoomByName(roomName);
	}
}

void GameWorld::LookAt(std::string target) {
	cout << "Looking at: " + target << endl;
	lookTarget(target);	 
}

void GameWorld::UseItem(std::string target1, std::string target2) {
	cout << "Using: " + target1 + " on " + target2 << endl;

}

void GameWorld::Open(std::string target) {
	cout << "Opening: " + target << endl;
	bool opened = false;
	for (int i = 0; i < (int)listOfItems.size() && !opened; ++i) {
		Item* itemOfList = listOfItems[i];
		if (itemOfList->entityName == target) {
			if (itemOfList->itemContained != nullptr) {
				opened = true;
				cout << "You open " << target << " and you find " << itemOfList->itemContained->entityName << " inside!" << endl;
				cout << "You add " << itemOfList->itemContained->entityName << " to your inventory, and discard "<< target <<" ."<< endl;
				player->inventory.push_back(itemOfList->itemContained);
			}
		}
	}
	if (!opened) cout << " The item cannot be opened." << endl;
}

void GameWorld::Take(std::string target) {
	cout << "Picking up: " + target << endl;
	bool found = false;
	for (list<Item*>::iterator it = player->actualRoom->listOfItems.begin(); it != player->actualRoom->listOfItems.end() && !found; ++it) {
		if ((*it)->entityName == target) {
			found = true;
			player->inventory.push_back((*it));
			cout << "You add " << target << " to your inventory." << endl;
		}
	}
	if (!found) cout << "The item " << target << " is not here to be picked up!" << endl;
}

void GameWorld::Drop(std::string target) {
	cout << "Dropping: " + target << endl;
	if (!player->inventory.empty()) {
		bool found = false;
		for (list<Item*>::iterator it = player->inventory.begin(); it != player->inventory.end() && !found; ++it) {
			if ((*it)->entityName == target) {
				found = true;
				player->actualRoom->listOfItems.push_back((*it));
				player->inventory.remove((*it));
				cout << "You drop " << target << " from your inventory into the room." << endl;
			}
		}
		if (!found) cout << "The item " << target << " is not in your inventory!" << endl;
	}
	else cout << "Your inventory is empty." << endl;
}