#include "Player.h"
#include "GameWorld.h"
#include <map>
using namespace std;

Player::Player(){
	entityName = "Player";
	entityDescription = "It's just me.";
	health = 20;
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

 int Player::playerUpdateHealth(int damage) {
	 health -= damage;
	 return health;
 }

 bool Player::isPlayerDead() {
	 return health <= 0;
 }

 Room* Player::getRoom() {
	 return actualRoom;
 }