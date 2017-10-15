#pragma once
#include"Entity.h"
#include <list>
#include <time.h>
#include <string>
#include <vector>

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
	std::vector<Item*> listOfItems;
	Player *player;

	void initGameWorld();
	void setPlayer(Player *p);
	void processInput(std::string input);
	void getParameters(std::string input, std::vector<std::string> *p);
	void printNumberArgumentsError(int argumentsNeeded, int argumentsProvided);
	Room* fetchRoomByName(std::string name);
	void lookTarget(std::string name);
	void MoveToDirection(std::string direction);
	void LookAt(std::string target);
	void UseItem(std::string target1, std::string target2);
	void Open(std::string target1);
	void Take(std::string target);
	void Drop(std::string target);
	

};

