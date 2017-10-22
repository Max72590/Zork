#pragma once
#include"Entity.h"
#include <list>
#include <string>
#include <vector>
#include <map>

enum exitName { NORTH, SOUTH, EAST, WEST, UP, DOWN };
	
class Room;
class Item;
class Player;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	std::vector<Room*> listOfRooms;
	std::vector< Item*> listOfItems;	
	std::map<std::string, Item*> replacements;
	std::map<std::string, Room*> keyToRoom;
	Player *player;

public:
	void initGameWorld();
	void setPlayer(Player *p);
	void processInput(std::string input);
	void getParameters(std::string input, std::vector<std::string> *p);
	void printNumberArgumentsError(int argumentsNeeded, int argumentsProvided);
	Room* fetchRoomByName(std::string name);
	void lookTarget(std::string name);
	void MoveToDirection(std::string direction);
	void LookAt(std::string target);
	void UseItemWith(std::string target1, std::string target2);
	void Open(std::string target1);
	void Take(std::string target);
	void Drop(std::string target);
	void Combine(std::string target1, std::string target2);
	void CheckInventory();
	void addItems(Item* list[], int size);
	void addRooms(std::vector<Room*> (&rooms));
	void addExitsToRooms(std::string  exitlist[][6],int size);
	void openRoom( Item* key);
	//void processItemUsage();
};

