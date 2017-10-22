#include "Item.h"

using namespace std;

Item::Item()
{
}

Item::Item(string name, string desc, bool pickable, bool key, Item* containedItem, Item* itemCombinedWith)
{
	entityName = name;
	entityDescription = desc;
	canBePickedUp = pickable;
	itemContained = containedItem;
	combinedWith = itemCombinedWith;
	isKey = key;
}

Item::~Item()
{
}

void Item::putItem( Item* itemToPut) {
	itemContained = itemToPut;
}

void Item::emptyItem() {
	itemContained = nullptr;
}