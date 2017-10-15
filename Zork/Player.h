#pragma once
#include "Entity.h"
//#include "Item.h"
//#include "Room.h"

#include <list>

class Room;
class Item;


class Player :
	public Entity
{
public:
	Player();
	~Player();

	void addItem(Item* item);
	void removeItem(Item* item);
	/*void MoveToDirection(std::string direction);
	void LookAt(std::string target);
	void UseItem(std::string target1, std::string target2);
	void Open(std::string target1);
	void Take(std::string target);
	void Drop(std::string target);*/

public:
	std::list<Item*> inventory;
	Room *actualRoom;

};

