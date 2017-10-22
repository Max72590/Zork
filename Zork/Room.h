#pragma once
#include "Entity.h"
#include <list>
#include <string>
#include <vector>
#include "Item.h"

class Room :
	public Entity
{
public:
	Room();
	~Room();
	Room(std::string name, std::string description, Item* lock);

	std::string getExit(int index);
	void setExits(std::string const (&exits)[6]);
	void unlock( Item* key);
	Item* fetchItemFromRoom(std::string target);

public:
	std::list< Item*> listOfItems;
	std::vector<std::string> listOfExits = std::vector<std::string>(6,"");
	 Item* lockedBy;
	
};

