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
	inventory[item->entityName] =item;
}

void Player::removeItem( Item* item) {
	inventory.erase(item->entityName);
}

 Item* const Player::fetchItem(string target) {
	 map<string, Item*>::iterator item = inventory.find(target);
	if (item != inventory.end()){
		if (item->second->entityName == target ) {
			return item->second;
		}
	}
	return nullptr;
}

 int Player::playerUpdateHealth(int damage) {
	 health -= damage;
	 return health;
 }

 bool const Player::isPlayerDead() {
	 return health <= 0;
 }

 Room* const Player::getRoom() {
	 return actualRoom;
 }