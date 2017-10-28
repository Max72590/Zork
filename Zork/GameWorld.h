#ifndef __GameWorld__
#define __GameWorld__

#include"Entity.h"
#include "Globals.h"


enum exitName { NORTH, SOUTH, WEST, EAST, UP, DOWN };
	
class Room;
class Item;
class Player;
class NPC;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	std::vector<Room*> listOfRooms;
	std::vector< Item*> listOfItems;	
	std::map<std::string, NPC*> listOfNPCs;
	std::map<std::string, Item*> replacements;
	std::map<std::string, Room*> keyToRoom;
	Player *player;
	NPC* dialoguingNPC;


public:
	void initGameWorld();
	void setPlayer(Player *p);
	void processInput(std::string const input);
	void getParameters(std::string const input, std::vector<std::string> *p);
	void const printNumberArgumentsError(int argumentsNeeded, int argumentsProvided);
	Room* const fetchRoomByName(std::string name);
	void addItems(Item* list[], int size);
	void addRooms(std::vector<Room*>(&rooms));
	void addExitsToRooms(std::string  exitlist[][6], int size);
	void openRoom(Item* key);
	void const win();
	int const checkState();
	clock_t const checkTime();
	bool const hasPlayerEnteredHouse();

	void const LookTarget(std::string name);
	void MoveToDirection(std::string direction);
	void UseItemWith(std::string target1, std::string target2);
	void Open(std::string target1);
	void Take(std::string target);
	void Drop(std::string target);
	void Combine(std::string target1, std::string target2);
	void const CheckInventory();
	void Talk(std::string target);
	void const Time();


private:
	bool winGame;
	bool enteredHouse;
	clock_t GameTime;
	int state, playerState;
};

#endif // __GameWorld__