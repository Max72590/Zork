#ifndef __Room__
#define __Room__
#include "Entity.h"
#include <list>
#include <string>
#include <vector>
#include <map>
#include "Item.h"
#include "NPC.h"

class Room :
	public Entity
{
public:
	Room();
	~Room();
	Room(std::string name, std::string description, Item* lock);

	std::string const getExit(int index);
	void setExits(std::string const (&exits)[6]);
	void unlock( Item* key);
	Item* const fetchItemFromRoom(std::string target);
	NPC* const fetchNPCFromRoom(std::string name);
	void addNPC(NPC* npc);
	void addItem(Item* item);

public:
	std::map<std::string, Item*> listOfItems;
	std::vector<std::string> listOfExits = std::vector<std::string>(6,"");
	std::map<std::string, NPC*> listOfRoomNPCs;
	Item* lockedBy;
	
};
#endif // __Room__
