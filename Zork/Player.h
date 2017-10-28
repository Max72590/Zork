#ifndef __Player__
#define __Player__
#include "Entity.h"
#include "Item.h"
#include "Globals.h"

class Room;



class Player :
	public Entity
{
public:
	Player();
	~Player();

	void addItem( Item* item);
	void removeItem( Item* item);
	 Item* const fetchItem(std::string target);
	 int playerUpdateHealth(int damage);
	 bool const isPlayerDead();
	 Room* const getRoom();

public:
	std::map<std::string, Item*> inventory;
	Room *actualRoom;
	int health;
};

#endif //__Player__