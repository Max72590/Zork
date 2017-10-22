#include "Player.h"
#include "GameWorld.h"
using namespace std;

Player::Player()
{
	entityName = "Player";
	entityDescription = "It's just me.";
}


Player::~Player()
{
}

void Player::addItem( Item* item) {
	inventory.push_back(item);
}

void Player::removeItem( Item* item) {
	inventory.remove(item);
}

 Item* Player::fetchItem(string target) {
	Item* item;
	for (list<Item*>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
		item = *it;
		if (item->entityName == target ) {
			return item;
		}
	}
	return nullptr;
}

 std::list<Item*> Player::fetchInventory() {
	 return inventory;
 }