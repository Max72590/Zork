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

NPC* Room::fetchNPCFromRoom(std::string name) {
	map<string, NPC*>::iterator it = listOfRoomNPCs.find(name);
	if (it != listOfRoomNPCs.end()) return (*it).second;
	else return nullptr;
}

void Room::addNPC(NPC* npc) {
	listOfRoomNPCs[(*npc).entityName] = npc;
}
