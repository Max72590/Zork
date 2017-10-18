#include "Room.h"
#include "GameWorld.h"

#include <iostream>
using namespace std;



Room::Room()
{
}

Room::Room(string name, string desc, bool lock) {
	entityName = name;
	entityDescription = desc;
	locked = lock;
}

Room::~Room()
{
}



void Room::checkIfKeyOpensRoom(string roomName) {
	if (roomName == entityName) {
		cout << "The key opens the door!" << endl;
		locked = false;
	}
}


string Room::getExit(int index) {
	return listOfExits[index];
}

void Room::setExits(vector<string>& exitNames) {
	listOfExits = exitNames;
}

void Room::addItems(list<Item*> itemsToAdd) {
	for (list<Item*>::iterator it = itemsToAdd.begin(); it != itemsToAdd.end(); ++it) {
		listOfItems.push_back(*it);
	}
	itemsToAdd.clear();
}