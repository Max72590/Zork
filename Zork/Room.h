#pragma once
#include "Entity.h"
#include <list>
#include <vector>

class Item;

class Room :
	public Entity
{
public:
	Room();
	~Room();
	Room(std::string name, std::string description, bool lock);

	void checkIfKeyOpensRoom(std::string name);
	std::string getExit(int index);
	void setExits(std::vector<std::string>exits);
	void addItem(Entity* item);
	void takeItem(std::string itemName);


public:
	std::list<Item*> listOfItems;
	std::vector<std::string> listOfExits = std::vector<std::string>(6,"");
	bool locked;
	
};

