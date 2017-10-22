#pragma once
#include "Entity.h"
#include <string>

class Item :
	public Entity
{
public:
	Item();
	Item(std::string name, std::string desc, bool pickable, bool isKey, Item* itemContained, Item* itemCombinedWith);
	~Item();
	void putItem( Item* itemToPut);
	void emptyItem();

public:
	bool canBePickedUp;
	bool isKey;
	Item* itemContained;
	const Item* combinedWith;

};

