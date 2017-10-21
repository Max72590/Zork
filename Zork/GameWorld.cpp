#include "GameWorld.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include <list>
#include <iostream>

using namespace std;

GameWorld::GameWorld()
{
}


GameWorld::~GameWorld()
{
}

void GameWorld::initGameWorld() {

	Item* entranceKey = new Item("House key", "A small key.", true, nullptr, nullptr);
	Item* entranceLock = new Item("Entrance Lock", "There's a lock, the door won't budge unless this lock is opened.", false, nullptr, entranceKey);
	Item* waterKey = new Item("Water key", "A small blue key with a teardrop symbol", true, nullptr, nullptr);
	Item* closedWindow = new Item("Closed window", "It's a window with its panels closed, it doesn't appear they're locked.",false, waterKey,nullptr);	
	Item* openedWindow = new Item("Window", "It's a window with its panels open, there's a good view of the outside.", false, nullptr, nullptr);
	Item* jug = new Item("Jug", "An empty water jug.", true, nullptr, nullptr);
	Item* filledJug = new Item("Filled jug", "A water jug filled with water, as it should be.", true, nullptr, nullptr);
	Item* lockedfaucet = new Item("Locked faucet", "It's a water faucet but there's a lock on it, you cannot get water from it in this state.", false, nullptr, waterKey);	
	Item* faucet = new Item("Water faucet", "It's a water faucet, now you can get water from it! If you have something to hold the water with, of course.", false, filledJug, jug);
	Item* fireplace = new Item("Fireplace", "A lit fireplace, it's warming the entire room... wait there's something on the back of the fireplace.",false, nullptr, filledJug);
	Item* fireplaceOff = new Item("Extinct fireplace", "An unlit fireplace, it's warming the entire room no more.", false, nullptr, nullptr);
	Item* room3Key = new Item("Blue key", "A blue colored key.", true, nullptr, nullptr);	
	Item* room3Lock = new Item("Blue lock","A blue colored lock is keeping the door locked.",false, nullptr, room3Key);
	Item* waxFigure = new Item("Wax figure", "A whole new wax candle. It has never been used", true, nullptr, nullptr);
	Item* room5Key = new Item("Green key", "A green colored key.", true, nullptr, nullptr);
	Item* room5Lock = new Item("Blue lock", "A blue colored lock is keeping the door locked.", false, nullptr, room5Key);	
	Item* stove = new Item("Stove", "A fully functional stove", false, room5Key, waxFigure);
	Item* bellStick = new Item("Bell stick", "A small stick, seems it can be used to play a bell", true, nullptr, nullptr);
	Item* bellBox = new Item("Metal box","A small metalic box with a bell shape etched into it", true, bellStick, nullptr);
	Item* bell = new Item();
	Item* room8Lock = new Item();
	Item* batteries = new Item();
	Item* torch = new Item();
	const Item* itemList[] = { entranceKey , waterKey, closedWindow, openedWindow, jug, filledJug, lockedfaucet, faucet, fireplace, fireplaceOff, room3Key, room3Lock, waxFigure, room5Key, room5Lock,
	 stove, bellStick, bellBox, bell, batteries, torch, room8Lock };
	addItems(itemList);
	
	Room* frontHouse = new Room("Front House", "You find yourself in front of a house, there's nothing here save for yourself and one exit at NORTH.", false);
	Room* rightHouse = new Room("Right House", "You arrived to the west side of the house, there's only a path going NORTH and SOUTH.", false);
	Room* leftHouse = new Room("Left House", "You arrived to the east side of the house, there's only a path going NORTH and SOUTH.", false);
	Room* backHouse = new Room("Back House", "You're in the back of the house, there is an exit at the EAST and the WEST.", false);
	Room* entrance = new Room("House Entrance", "You're in the entrance room, there is an exit at the EAST and the WEST and a trapdoor.", false);
	Room* basement = new Room("House Basement", "You descended into the basement, there's nothing there save for an strange robed figure sitting in the back of the room.",true);
	Room* Room2 = new Room("Room2", "You're in Room 2", false);
	Room* Room3 = new Room("Room3", "You're in Room 3", true);
	Room* Room4 = new Room("Room4", "You're in Room 4", false);
	Room* Room5 = new Room("Room5", "You're in Room 5", true);
	Room* Room6 = new Room("Room6", "You're in Room 6", false);
	Room* Room7 = new Room("Room7", "You're in Room 7", false);
	Room* Room8 = new Room("Room8", "You're in Room 8", true);
	addRooms({frontHouse, rightHouse,leftHouse,backHouse,entrance,Room2,Room3,Room4, Room5, Room6, Room7, Room8, basement });

	frontHouse->listOfItems.push_back(entranceLock);
	backHouse->listOfItems.push_back(entranceKey);
	entrance->listOfItems.push_back(jug);
	Room2->listOfItems.push_back(fireplace);
	Room2->listOfItems.push_back(closedWindow);
	Room2->listOfItems.push_back(room3Lock);
	Room3->listOfItems.push_back(waxFigure);
	Room4->listOfItems.push_back(stove);
	Room4->listOfItems.push_back(lockedfaucet);
	Room4->listOfItems.push_back(room5Lock);
	Room5->listOfItems.push_back(bellBox);
	
	replacements[fireplace->entityName] = fireplaceOff;
	replacements[closedWindow->entityName] = openedWindow;
	replacements[lockedfaucet->entityName] = faucet;

	const string  listOfExits[12][6] = { { "House Entrance","","Right House","Left House","","" },
	{ "Back House","Front House","","","","" }, { "Back House","Front House","","","","" },
	{ "","","Right House","Left House","","" }, { "","Front House","Room4","Room2","","House Basement" },
	{ "Room3","","House Entrance","","","" },{ "","Room2","","","","" },
	{ "Room5","","","House Entrance","","" },{ "","Room4","","Room6","","" },{ "","","Room5","","Room7","" },
	{ "","Room8","","","","Room6" },{ "Room7","","","","","" } };
	addExitsToRooms(listOfExits);

	player->actualRoom = frontHouse;
}

void GameWorld::setPlayer(Player *p) {
	player = p;
}

void GameWorld::processInput(string input) {
	cout << "Processing input: " << input << endl;
	if (!input.empty()) {
		vector<string> parameters;
		getParameters(input, &parameters);
		if (parameters.size() >= 1) {
			string command = parameters[0];
			if (command == "LOOK") {
				if (parameters.size()-1 > 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else {
					if (parameters.size() == 1) LookAt("this room") ;
					else LookAt(parameters[1]);
				}
			}
			else if (command == "USE") {
				if (parameters.size()-1 != 3) printNumberArgumentsError(3, ((int)parameters.size()) - 1);
				else UseItem(parameters[1], parameters[3]);
			}
			else if (command == "NORTH" || command == "SOUTH" || command == "EAST" || command == "WEST" || command == "UP" || command == "DOWN") {
				if (parameters.size()-1 != 0) printNumberArgumentsError(0, ((int)parameters.size()) - 1);
				else MoveToDirection(parameters[0]);
			}
			else if (command == "OPEN") {
				if (parameters.size()-1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else Open(parameters[1]);
			}
			else if (command == "TAKE") {
				if (parameters.size()-1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else Take(parameters[1]);
			}
			else if (command == "DROP") {
				if (parameters.size()-1 > 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
				else Drop(parameters[1]);
			}
			else {
				cout << "Command not recognized" << endl;
			}
		}
		else cout << "Not enough arguments" << endl;
	}
}

void GameWorld::getParameters(string input, vector<string> *params) {
	string parameter;
	for (int i = 0; i < (int)input.size(); ++i) {
		if (i == input.size() - 1) {
			parameter.push_back(input[i]);
			params->push_back(parameter);
			parameter.clear();
		}
		else if (input[i] != ' ' ) parameter.push_back(input[i]);
		else {
			params->push_back(parameter);
			parameter.clear();
		}
	}

} 

Room* GameWorld::fetchRoomByName(string name) {
	for (Room* it : listOfRooms) {
		if ( it->entityName == name) return it;
	}
	return nullptr;
}

void GameWorld::lookTarget(string name) {
	list<const Item*> *roomItems = &player->actualRoom->listOfItems;
	bool found = false;
	if (name == "me" || name == "myself") {
		cout << player->entityDescription << endl;
		found = true;
	}
	else if (name == "this room") {
		cout << player->actualRoom->entityDescription << endl;
		found = true;
	}
	else if (!found && name == player->actualRoom->entityName) {
		cout << player->actualRoom->entityDescription << endl;
		found = true;
		if (!(*roomItems).empty()) {
			cout << "You see several things in the room:" << endl;
			for (list<const Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end(); ++it) cout << "There's " <<(*it)->entityDescription << endl;
		}
	}
	else {
		if (!(*roomItems).empty()) {
			for (list<const Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end() && !found; ++it) {
				if ((*it)->entityName == name) {
					cout << (*it)->entityDescription << endl;
					found = true;
				}
			}
		}
	}
	if (!found) cout << "I cannot find " << name << " to look at."<<endl;
}

void GameWorld::printNumberArgumentsError(int argumentsNeeded, int argumentsProvided) {
	cout << "Error number of arguments invalid, arguments needed: " << argumentsNeeded << " arguments provided: " << argumentsProvided << endl;
}

void GameWorld::MoveToDirection(std::string direction) {
	int roomIndex;
	if (direction == "NORTH") roomIndex = NORTH;
	else if (direction == "SOUTH") roomIndex = SOUTH;
	else if (direction == "EAST") roomIndex = EAST;
	else if (direction == "WEST") roomIndex = WEST;
	else if (direction == "UP") roomIndex = UP;
	else if (direction == "DOWN") roomIndex = DOWN;
	else cout << "I cannot understand what direction " << direction << " is." << endl;
	string roomName = player->actualRoom->getExit(roomIndex);
	if (!roomName.empty()) {
		cout << "Moving to direction: " + roomName << endl;
		Room* targetRoom = fetchRoomByName(roomName);
		if (!targetRoom->locked) {
			player->actualRoom = targetRoom;
			cout << targetRoom->entityDescription << endl;
		}
		else cout << "The entrance to the room in the "<< direction <<" direction is locked." << endl;
	}
	else cout << "There's no exit in direction: " << direction << endl;
}

void GameWorld::LookAt(std::string target) {
	cout << "Looking at: " + target << endl;
	lookTarget(target);	 
}

void GameWorld::UseItem(std::string target1, std::string target2) {
	cout << "Using: " + target1 + " on " + target2 << endl;

}

void GameWorld::Open(std::string target) {
	cout << "Opening: " + target << endl;
	bool opened, found, inInventory;
	opened = found = inInventory = false;
	const Item* itemOfList = nullptr;
	for (list<const Item*>::iterator it = player->inventory.begin(); it != player->inventory.end() && !found; ++it) {
		itemOfList = *it;
		if (itemOfList->entityName == target) {
			found = true;
			if (itemOfList->itemContained != nullptr) {
				opened = true;
				inInventory = true;
			}
		}
	}	
	if (!found) {		
		for (list<const Item*>::iterator it = player->actualRoom->listOfItems.begin(); it != player->actualRoom->listOfItems.end() && !found; ++it) {
			itemOfList = *it;
			if (itemOfList->entityName == target) {
				found = true;
				if (itemOfList->itemContained != nullptr) {
					opened = true;	
				}
			}
		}
		if (!found) cout << "The item " << target << " is not here to be picked up!" << endl;
	}
	else {
		if (!opened) cout << " The item cannot be opened." << endl;
		else {
			player->inventory.push_back(itemOfList->itemContained);
			cout << "You open " << target << " and you find " << itemOfList->itemContained->entityName << " inside!" << endl;
			cout << "You add " << itemOfList->itemContained->entityName << " to your inventory, and discard " << target << " ." << endl;
			if (inInventory) player->inventory.remove(itemOfList);
			else player->actualRoom->listOfItems.remove(itemOfList);
		}
	}
}

void GameWorld::Take(std::string target) {
	cout << "Picking up: " + target << endl;
	bool found = false;
	const Item* roomItem = nullptr;
	for (list<const Item*>::iterator it = player->actualRoom->listOfItems.begin(); it != player->actualRoom->listOfItems.end() && !found; ++it) {
		if ((*it)->entityName == target) {
			if ((*it)->canBePickedUp) {
				found = true;
				player->inventory.push_back((*it));
				roomItem = *it;
				cout << "You add " << target << " to your inventory." << endl;
			}
			else cout << target << " is locked in place and cannot be picked up" << endl;
		}
	}
	if (!found) cout << "The item " << target << " is not here to be picked up!" << endl;
	else  player->actualRoom->listOfItems.remove(roomItem);
}

void GameWorld::Drop(std::string target) {
	cout << "Dropping: " + target << endl;
	if (!player->inventory.empty()) {
		bool found = false;
		const Item* iter = nullptr;
		for (list<const Item*>::iterator it = player->inventory.begin(); it != player->inventory.end() && !found; ++it) {
			if ((*it)->entityName == target) {
				found = true;
				player->actualRoom->listOfItems.push_back((*it));
				iter = *it;
				cout << "You drop " << target << " from your inventory into the room." << endl;
			}
		}
		if (!found) cout << "The item " << target << " is not in your inventory!" << endl;
		else player->inventory.remove(iter);
	}
	else cout << "Your inventory is empty." << endl;
}

void GameWorld::addItems(const Item* (&list)[22]) {
	for (int i = 0; i < 22; ++i) listOfItems.push_back(list[i]);
}

void GameWorld::addRooms( Room* const(&rooms)[13]) {
	for (int i = 0; i < 12; ++i) listOfRooms.push_back(rooms[i]);
}

void GameWorld::addExitsToRooms(string const (&exitlist)[12][6]) {
	for (int i = 0; i < 12; ++i) listOfRooms[i]->setExits(exitlist[i]);
}

