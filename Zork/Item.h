#pragma once
#include "Entity.h"
#include <string>

enum itemType {OBJECT, DOOR};

class Item :
	public Entity
{
public:
	Item();
	Item(std::string name, std::string desc, bool combinable, bool key, Item* itemContained);
	~Item();

public:
	bool combinable ;
	bool key;
	int keyOfEntity;
	Item* itemContained;
};

