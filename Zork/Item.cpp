#include "Item.h"

using namespace std;

Item::Item()
{
}

Item::Item(string name, string desc, bool pickable, Item* containedItem, Item* combinedWith)
{
	entityName = name;
	entityDescription = desc;
	canBePickedUp = pickable;
	itemContained = containedItem;
	puzzleSolution = combinedWith;
}

Item::~Item()
{
}
