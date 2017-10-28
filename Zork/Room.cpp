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



string const Room::getExit(int index) {
	return listOfExits[index];
}

void Room::setExits(string const (&exits)[6]) {
	for (int i = 0; i < 6; ++i) listOfExits[i] = exits[i];
}

void Room::unlock( Item* key) {
	if (key->entityName == lockedBy->entityName)
		lockedBy = nullptr;
}

Item* const Room::fetchItemFromRoom(string target) {
	map<string, Item*>::iterator itemIt = listOfItems.find(target);
	if (itemIt != listOfItems.end()){
			return itemIt->second;
	}
	return nullptr;
}

NPC* const Room::fetchNPCFromRoom(std::string name) {
	map<string, NPC*>::iterator it = listOfRoomNPCs.find(name);
	if (it != listOfRoomNPCs.end()) return (*it).second;
	else return nullptr;
}

void Room::addNPC(NPC* npc) {
	listOfRoomNPCs[(*npc).entityName] = npc;
}

void Room::addItem(Item* item) {
	listOfItems[item->entityName] = item;
}
