#pragma once
#include "Entity.h"
#include <string>

enum itemType {OBJECT, DOOR};

class Item :
	public Entity
{
public:
	Item();
	Item(std::string name, std::string desc, bool pickable, Item* itemContained, Item* combinedWith);
	~Item();

public:
	int keyOfEntity;
	bool canBePickedUp;
	Item* itemContained;
	Item* puzzleSolution;
};

