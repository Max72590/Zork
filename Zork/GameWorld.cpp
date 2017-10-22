#include "GameWorld.h"
#include "Globals.h"
#include "Player.h"
#include "Room.h"
#include "Item.h"

using namespace std;

GameWorld::GameWorld()
{
	winGame = false;
}


GameWorld::~GameWorld()
{
}

void GameWorld::initGameWorld() {

	Item* entranceKey = new Item("House_key", "A small key.", true, true, nullptr, nullptr);
	Item* entranceLock = new Item("Entrance_lock", "There's a lock, the door won't budge unless this lock is opened.", false, false, nullptr, entranceKey);
	Item* waterKey = new Item("Water_key", "A small blue key with a waterdrop symbol", true, false, nullptr, nullptr);
	Item* closedWindow = new Item("Closed_window", "It's a window with its panels closed, it doesn't appear they're locked.",false, false, waterKey,nullptr);
	Item* openedWindow = new Item("Window", "It's a window with its panels open, there's a good view of the outside.", false, false, nullptr, nullptr);
	Item* jug = new Item("Jug", "An empty water jug.", true, false, nullptr, nullptr);
	Item* filledJug = new Item("Filled_jug", "A water jug filled with water, as it should be.", true, false, nullptr, nullptr);
	Item* lockedfaucet = new Item("Locked_faucet", "It's a water faucet but there's a lock on it, you cannot get water from it in this state.", false, false, nullptr, waterKey);
	Item* faucet = new Item("Faucet", "It's a water faucet, now you can get water from it! If you have something to hold the water with, of course.", false, false, nullptr, jug);
	Item* room3Key = new Item("Blue_key", "A blue colored key.", true, true, nullptr, nullptr);
	Item* room3Lock = new Item("Blue_lock", "A blue colored lock is keeping the door locked.", false, false, nullptr, room3Key);
	Item* fireplace = new Item("Fireplace", "A lit fireplace, it's warming the entire room... wait there's something on the back of the fireplace.",false, false, nullptr, filledJug);
	Item* fireplaceOff = new Item("Fireplace_box", "Inside the fireplace there's a box.", false, false, room3Key, nullptr);
	Item* waxFigure = new Item("Wax_figure", "A whole new wax candle. It has never been used", true, false, nullptr, nullptr);
	Item* room5Key = new Item("Green_key", "A green colored key.", true, true, nullptr, nullptr);
	Item* room5Lock = new Item("Green_lock", "A blue colored lock is keeping the door locked.", false, false, nullptr, room5Key);
	Item* stove = new Item("Stove", "A fully functional stove", false, false, nullptr, waxFigure);
	Item* bellStick = new Item("Bell-clapper", "A silver bell-clapper, seems it can be used in conjunction with a bell", true, false, nullptr, nullptr);
	Item* bellBox = new Item("Metal_box","A small metalic box with a bell shape etched into it", true, false, bellStick, nullptr);
	Item* bell = new Item("Bell", "A small metalic bell",true, false, nullptr, bellStick);
	Item* room8Lock = new Item("Strange_lock","This lock unlike the others doesn't have a keyhole but a musical symbol etched into it.", false, false, nullptr,bell);
	Item* antidote = new Item("Bottle","A green bottle filled with liquid, the tag says: Antidote ",true,false,nullptr,nullptr);
	Item* note = new Item("Note","Congratulations on getting inside this house, i don't think you noticed but the door pommel was poisoned. A special poison that it's absorbed through your skin, you have about 20 minutes of live, spend them well.", true, false, nullptr, nullptr);

	Item* itemList[] = { entranceKey , waterKey, closedWindow, openedWindow, jug, filledJug, lockedfaucet, faucet, fireplace, fireplaceOff, room3Key, room3Lock, waxFigure, room5Key, room5Lock,
	 stove, bellStick, bellBox, bell, room8Lock, antidote,note};
	addItems(itemList, 22);
	
	Room* frontHouse = new Room("Front House", "You find yourself in front of a house, there's nothing here save for yourself and one exit at NORTH.", nullptr);
	Room* rightHouse = new Room("Right House", "You arrived to the west side of the house, there's only a path going NORTH and SOUTH.", nullptr);
	Room* leftHouse = new Room("Left House", "You arrived to the east side of the house, there's only a path going NORTH and SOUTH.", nullptr);
	Room* backHouse = new Room("Back House", "You're in the back of the house, there is an exit at the EAST and the WEST.", nullptr);
	Room* entrance = new Room("House Entrance", "You're in the entrance room, there is an exit at the EAST and the WEST and a trapdoor.", nullptr);//entranceKey);
	Room* Room2 = new Room("Room2", "You're in Room 2", nullptr);
	Room* Room3 = new Room("Room3", "You're in Room 3", room3Key);
	Room* Room4 = new Room("Room4", "You're in Room 4", nullptr);
	Room* Room5 = new Room("Room5", "You're in Room 5", room5Key);
	Room* Room6 = new Room("Room6", "You're in Room 6", nullptr);
	Room* Room7 = new Room("Room7", "You're in Room 7", nullptr);
	Room* Room8 = new Room("Room8", "You descended into the basement, there's nothing there save for an strange robed figure sitting in the back of the room.", bell);
	Room* rooms[] = { frontHouse, rightHouse,leftHouse,backHouse,entrance,Room2,Room3,Room4, Room5, Room6, Room7, Room8 };
	vector<Room*> r(rooms, rooms +sizeof(rooms) / sizeof(rooms[0]));
	addRooms(r);

	frontHouse->listOfItems.push_back(entranceLock);
	backHouse->listOfItems.push_back(entranceKey);
	entrance->listOfItems.push_back(jug);
	entrance->listOfItems.push_back(note);
	Room2->listOfItems.push_back(fireplace);
	Room2->listOfItems.push_back(closedWindow);
	Room2->listOfItems.push_back(room3Lock);
	Room3->listOfItems.push_back(waxFigure);
	Room3->listOfItems.push_back(bell);
	Room4->listOfItems.push_back(stove);
	Room4->listOfItems.push_back(lockedfaucet);
	Room4->listOfItems.push_back(room5Lock);
	Room5->listOfItems.push_back(bellBox);
	Room7->listOfItems.push_back(room8Lock);
	Room8->listOfItems.push_back(antidote);
	
	replacements[closedWindow->entityName] = openedWindow;
	replacements[fireplace->entityName] = fireplaceOff;
	replacements[closedWindow->entityName] = openedWindow;
	replacements[lockedfaucet->entityName] = faucet;
	replacements[faucet->entityName] = filledJug;
	replacements[stove->entityName] = room5Key;
	keyToRoom[entranceKey->entityName] = entrance;
	keyToRoom[room3Key->entityName] = Room3;
	keyToRoom[room5Key->entityName] = Room5;
	keyToRoom[bell->entityName] = Room8;

	string  listOfExits[12][6] = { { "House Entrance","","Right House","Left House","","" },
	{ "Back House","Front House","","","","" }, { "Back House","Front House","","","","" },
	{ "","","Right House","Left House","","" }, { "","Front House","Room4","Room2","","House Basement" },
	{ "Room3","","House Entrance","","","" },{ "","Room2","","","","" },
	{ "Room5","","","House Entrance","","" },{ "","Room4","","Room6","","" },{ "","","Room5","","Room7","" },
	{ "","Room8","","","","Room6" },{ "Room7","","","","","" } };
	addExitsToRooms(listOfExits, 12);

	player->actualRoom = frontHouse;
	cout<<player->actualRoom->entityDescription << endl;
	cout << endl;
	cout << endl;
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
				else UseItemWith(parameters[1], parameters[3]);
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
			else if (command == "COMBINE") {
				if (parameters.size() - 1 != 3) printNumberArgumentsError(3, ((int)parameters.size()) - 1);
				else Combine(parameters[1], parameters[3]);
			}
			else if (command == "INVENTORY") {
				if (parameters.size() - 1 > 0) printNumberArgumentsError(0, ((int)parameters.size()) - 1);
				else CheckInventory();
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


void GameWorld::printNumberArgumentsError(int argumentsNeeded, int argumentsProvided) {
	cout << "Error number of arguments invalid, arguments needed: " << argumentsNeeded << " arguments provided: " << argumentsProvided << endl;
}

void GameWorld::MoveToDirection(string direction) {
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
		if (targetRoom->lockedBy == nullptr) {
			player->actualRoom = targetRoom;
			cout << targetRoom->entityDescription << endl;
			for (list<Item*>::iterator it = targetRoom->listOfItems.begin(); it != targetRoom->listOfItems.end(); ++it) {
				cout << "There's an item: " << (*it)->entityName << endl;
			}
		}
		else cout << "The entrance to the room in the "<< direction <<" direction is locked." << endl;
	}
	else cout << "There's no exit in direction: " << direction << endl;
}

void GameWorld::LookAt(string target) {
	cout << "Looking at: " + target << endl;
	lookTarget(target);	 
}

void GameWorld::lookTarget(string name) {
	list<Item*> *roomItems = &player->actualRoom->listOfItems;
	bool found = false;
	if (name == "me" || name == "myself") {
		cout << player->entityDescription << endl;
		found = true;
	}
	else if (name == "this room") {
		cout << player->actualRoom->entityDescription << endl;
		for (list<Item*>::iterator it = player->actualRoom->listOfItems.begin(); it != player->actualRoom->listOfItems.end(); ++it) {
			cout << "There the item: " << (*it)->entityName << endl;
		}
		found = true;
	}
	else if (!found && name == player->actualRoom->entityName) {
		cout << player->actualRoom->entityDescription << endl;
		found = true;
		if (!(*roomItems).empty()) {
			cout << "You see several things in the room:" << endl;
			for (list<Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end(); ++it) cout << "There's " << (*it)->entityDescription << endl;
		}
	}
	else {
		if (!(*roomItems).empty()) {
			for (list<Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end() && !found; ++it) {
				if ((*it)->entityName == name) {
					cout << (*it)->entityDescription << endl;
					found = true;
				}
			}
		}
	}
	if (!found) cout << "I cannot find " << name << " to look at." << endl;
}

void GameWorld::UseItemWith(string target1, std::string target2) {
	cout << "Using: " + target1 + " on " + target2 << endl;
	if (target1 != target2) {
		pair< Item*,  Item*> itemPair(nullptr, nullptr);
		itemPair.first = player->fetchItem(target1);
		if (itemPair.first == nullptr) itemPair.first = player->actualRoom->fetchItemFromRoom(target1);
		itemPair.second = player->fetchItem(target2);
		if (itemPair.second == nullptr) itemPair.second = player->actualRoom->fetchItemFromRoom(target2);
		if (itemPair.first != nullptr && itemPair.second != nullptr) {
			Item* combinationItem = nullptr;
			Item* toBeCombined = nullptr;
			if (itemPair.second->combinedWith != nullptr) {
				  combinationItem = itemPair.first;
				  toBeCombined = itemPair.second;
			}
			else if (itemPair.first->combinedWith != nullptr) {
				  combinationItem = itemPair.second;
				  toBeCombined = itemPair.first;
			}
			if (toBeCombined != nullptr && combinationItem!= nullptr) {
				cout << "toBeCombined is: " << toBeCombined->entityName << " combinationItem is: " << combinationItem->entityName << endl;
				if (combinationItem->entityName == toBeCombined->combinedWith->entityName){
					if (combinationItem->isKey) {
						openRoom(combinationItem);
						player->actualRoom->listOfItems.remove(toBeCombined);
					}
					else {
						map<string, Item*>::iterator it = replacements.find(toBeCombined->entityName);
						if (it != replacements.end()) {
							if ((*it).second->canBePickedUp) {
								cout << "You successfully combined " << combinationItem->entityName << " with " << toBeCombined->entityName << " recieving: " << (*it).second->entityName << endl;
								cout << "You add " << (*it).second->entityName << " to your inventory." << endl;
								player->addItem((*it).second);
								player->removeItem(combinationItem);
							}
							else {
								cout << "You successfully combined " << combinationItem->entityName << " with " << toBeCombined->entityName<<endl;
								player->actualRoom->listOfItems.remove(toBeCombined);
								player->actualRoom->listOfItems.push_back((*it).second);
								cout << "And " << toBeCombined->entityName << " becomes " << (*it).second->entityName <<endl;
							}
						}
						else cout << "Couldn't find the replacement for " << toBeCombined->entityName << endl;
					}
				}
				else cout << "You cannot combine " << target1 << " with " << target2 << "." << endl;
			}
			else cout << "You cannot use " << target1 << " with " << target2 <<"."<< endl;
		}
		else {
			if (itemPair.first != nullptr) cout << "You only have " << itemPair.first->entityName << " but the other item is nowhere to be found." << endl;
			else if (itemPair.second != nullptr) cout << "You only have " << itemPair.second->entityName << " but the other item is nowhere to be found." << endl;
			else cout << "You have neither of those items." << endl;
		}
	}
	else cout << "I cannot use the item with itself." << endl;
}

void GameWorld::Open(string target) {
	cout << "Opening: " + target << endl;
	bool opened, inInventory;
	opened = inInventory = false;
	 Item* itemOfList =player->fetchItem(target);
	if (itemOfList!= nullptr && itemOfList->itemContained != nullptr) {
		opened = true;
		inInventory = true;
		if (itemOfList->entityName == "Bell") {
			itemOfList->isKey = false;
		}
	}
	if (itemOfList == nullptr) {
		itemOfList = player->actualRoom->fetchItemFromRoom(target);				
		if (itemOfList != nullptr && itemOfList->itemContained != nullptr) {
			opened = true;	
		}
		if (itemOfList->itemContained == nullptr) cout << "The item " << target << " is empty!" << endl;
		if (itemOfList == nullptr) cout << "The item " << target << " is not here to be opened!" << endl;
	}
	if (itemOfList != nullptr) {
		if (!opened) cout << " The item cannot be opened." << endl;
		else {
			player->inventory.push_back(itemOfList->itemContained);
			cout << "You open " << target << " and you find " << itemOfList->itemContained->entityName << " inside!" << endl;
			cout << "You add " << itemOfList->itemContained->entityName << " to your inventory";				
			if (inInventory) { 
				//player->inventory.remove(itemOfList); 
				//cout << ", and discard " << target << " ." << endl;
				itemOfList->itemContained = nullptr;
				cout << "I should not be discarding this" << endl;
			}
			else {
				//player->actualRoom->listOfItems.remove(itemOfList);
				map<string,  Item*>::iterator it = replacements.find(itemOfList->entityName);
				itemOfList->itemContained = nullptr;
				if ( it != replacements.end()) {					
					player->actualRoom->listOfItems.remove(itemOfList);
					player->actualRoom->listOfItems.push_back((*it).second);
				}
			}
		}
	}
}

void GameWorld::Take(string target) {
	cout << "Picking up: " + target << endl;
	bool found = false;
	Item* roomItem = player->actualRoom->fetchItemFromRoom(target);
	if (roomItem != nullptr){
		if (roomItem->entityName == target) {
			if (roomItem->canBePickedUp) {
				found = true;
				player->inventory.push_back(roomItem);
				cout << "You add " << target << " to your inventory." << endl;
				if (roomItem->entityName == "Bottle") win();
			}
			else cout << target << " is locked in place and cannot be picked up" << endl;
		}
	}
	if (!found) cout << "The item " << target << " is not here to be picked up!" << endl;
	else  player->actualRoom->listOfItems.remove(roomItem);
}

void GameWorld::Drop(string target) {
	cout << "Dropping: " + target << endl;
	if (!player->inventory.empty()) {
		bool found = false;
		Item* iter = player->fetchItem(target);
		if (iter != nullptr) {
			if (iter->entityName == target) {
				found = true;
				player->actualRoom->listOfItems.push_back(iter);
				cout << "You drop " << target << " from your inventory into the room." << endl;
			}
		}
		if (!found) cout << "The item " << target << " is not in your inventory!" << endl;
		else player->inventory.remove(iter);
	}
	else cout << "Your inventory is empty." << endl;
}

void GameWorld::Combine(string target1, string target2) {
	cout << "Combining: " + target1 << " with "<<target2<< endl;
	Item* itemToPut = player->fetchItem(target1);
	if (itemToPut != nullptr) {
		Item* receivingItem = player->fetchItem(target2);
		if (receivingItem != nullptr && receivingItem->itemContained == nullptr) {
			if (receivingItem->entityName == "Metal_box") {
				receivingItem->putItem(itemToPut);
				cout << "You put " << target1 << " inside Metal_box" << endl;
			}
			if ((receivingItem->entityName == "Bell" && itemToPut->entityName == "Bell-clapper")) {
				cout << "You attached the bell-clapper to the bell, now the bell can be played, maybe you can USE it on something." << endl;
				receivingItem->isKey = true;
				receivingItem->putItem(itemToPut);
				player->removeItem(itemToPut);
			}
			else cout << "Cannot combine these items" << endl;
		}
		else {
			receivingItem = player->actualRoom->fetchItemFromRoom(target2);
			if (receivingItem != nullptr && !receivingItem->canBePickedUp && receivingItem->itemContained == nullptr) {
				receivingItem->putItem(itemToPut);
				cout << "You put " << target1 << " inside " << target2<<" .";
			}
			else cout << "You cannot put " << target1 << " inside "<< target2 << endl;
		}
	}
	else cout << "No item: " << target1 << " found in inventory." << endl;
}

void GameWorld::CheckInventory() {
	list<Item*> inventory = player->fetchInventory();
	for (list<Item*>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
		cout << (*it)->entityName << endl;
	}
}

void GameWorld::addItems(Item* list[], int size) {
	for (int i = 0; i < size; ++i) listOfItems.push_back(list[i]);
}

void GameWorld::addRooms(vector<Room*> (&rooms)) {
	for (int i = 0; i < 12; ++i) listOfRooms.push_back(rooms[i]);
}

void GameWorld::addExitsToRooms(string  exitlist[][6], int size) {
	for (int i = 0; i < size; ++i) listOfRooms[i]->setExits(exitlist[i]);
}

void GameWorld::openRoom( Item* key) {
	map<string, Room*>::iterator it = keyToRoom.find(key->entityName);
	if (it != keyToRoom.end()) {
		(*it).second->unlock(key);
		cout << "You unlocked the next room!" << endl;
	}
	else cout << "This key doesn't open the door." << endl;
}

void GameWorld::win() {
	cout << "You drink the antidote as fast as you can."<<endl;
	cout << "Your body starts to stabilize and the poison inside your body is neutralized" << endl;
	cout << "You survived through this one by the skin of your teeth. Well played." << endl;
	winGame = true;
}
bool GameWorld::getWin() {
	return winGame;
}