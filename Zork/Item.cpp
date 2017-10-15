#include "Item.h"

using namespace std;

Item::Item()
{
}

Item::Item(string name, string desc, bool isCombinable, bool isKey, Item* containedItem)
{
	entityName = name;
	entityDescription = desc;
	combinable = isCombinable;
	key = isKey;
	itemContained = containedItem;
}

Item::~Item()
{
}
