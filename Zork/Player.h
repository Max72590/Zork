#pragma once
#include "Entity.h"
#include "Item.h"
#include <list>

class Room;



class Player :
	public Entity
{
public:
	Player();
	~Player();

	void addItem( Item* item);
	void removeItem( Item* item);
	 Item* fetchItem(std::string target);
	 std::list<Item*> fetchInventory();
	 int playerUpdateHealth(int damage);
	 bool isPlayerDead();
	 Room* getRoom();

public:
	std::list<Item*> inventory;
	Room *actualRoom;
	int health;
};

