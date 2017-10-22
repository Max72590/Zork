#include "Room.h"
#include "GameWorld.h"
using namespace std;



Room::Room()
{
}

Room::Room(string name, string desc,  Item* lock) {
	entityName = name;
	entityDescription = desc;
	lockedBy = lock;
}

Room::~Room()
{
}



string Room::getExit(int index) {
	return listOfExits[index];
}

void Room::setExits(string const (&exits)[6]) {
	for (int i = 0; i < 6; ++i) listOfExits[i] = exits[i];
}

void Room::unlock( Item* key) {
	if (key->entityName == lockedBy->entityName)
		lockedBy = nullptr;
}

Item* Room::fetchItemFromRoom(std::string target) {
	 Item* item;
	for (list< Item*>::iterator it = listOfItems.begin(); it != listOfItems.end(); ++it) {
		item = *it;
		if (item->entityName == target) {
			return item;
		}
	}
	return nullptr;
}
