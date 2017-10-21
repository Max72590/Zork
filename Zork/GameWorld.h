#pragma once
#include"Entity.h"
#include <list>
#include <time.h>
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
	std::vector<const Item*> listOfItems;
	std::map<std::string, Item*> replacements;
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
	void UseItem(std::string target1, std::string target2);
	void Open(std::string target1);
	void Take(std::string target);
	void Drop(std::string target);
	void addItems(const Item* (&list)[22]);
	void addRooms(Room* const (&rooms)[13]);
	void addExitsToRooms(std::string const (&exitlist)[12][6]);

};

