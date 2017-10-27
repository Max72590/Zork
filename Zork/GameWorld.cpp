#include "GameWorld.h"
#include "Globals.h"
#include "Player.h"
#include "Room.h"
#include "NPC.h"
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

	Item* entranceKey = new Item("House_key", ENTRANCE_KEY_DESC, true, true, nullptr, nullptr);
	Item* entranceLock = new Item("Entrance_lock", ENTRANCE_LOCK, false, false, nullptr, entranceKey);
	Item* waterKey = new Item("Water_key", WATER_KEY, true, false, nullptr, nullptr);
	Item* closedWindow = new Item("Closed_window", WINDOW_CLOSED,false, false, waterKey,nullptr);
	Item* openedWindow = new Item("Window", WINDOW_OPEN, false, false, nullptr, nullptr);
	Item* jug = new Item("Jug", JUG, true, false, nullptr, nullptr);
	Item* filledJug = new Item("Filled_jug", JUG_FILLED, true, false, nullptr, nullptr);
	Item* lockedfaucet = new Item("Locked_faucet", LOCKED_FAUCET, false, false, nullptr, waterKey);
	Item* faucet = new Item("Faucet", FAUCET, false, false, nullptr, jug);
	Item* room3Key = new Item("Blue_key", ROOM3_KEY, true, true, nullptr, nullptr);
	Item* room3Lock = new Item("Blue_lock", ROOM3_LOCK, false, false, nullptr, room3Key);
	Item* fireplace = new Item("Fireplace", FIREPLACE,false, false, nullptr, filledJug);
	Item* fireplaceOff = new Item("Fireplace_box", FIREPLACE_OFF, false, false, room3Key, nullptr);
	Item* waxFigure = new Item("Wax_figure", WAXFIGURE, true, false, nullptr, nullptr);
	Item* room5Key = new Item("Green_key", ROOM5_KEY, true, true, nullptr, nullptr);
	Item* room5Lock = new Item("Green_lock", ROOM5_LOCK, false, false, nullptr, room5Key);
	Item* stove = new Item("Stove", STOVE, false, false, nullptr, waxFigure);
	Item* bellStick = new Item("Bell-clapper", BELL_CLAPPER, true, false, nullptr, nullptr);
	Item* bellBox = new Item("Metal_box", BELL_BOX, true, false, bellStick, nullptr);
	Item* bell = new Item("Bell", BELL,true, false, nullptr, bellStick);
	Item* room8Lock = new Item("Strange_lock",ROOM8_LOCK, false, false, nullptr,bell);
	Item* note = new Item("Note",NOTE, true, false, nullptr, nullptr);

	Item* itemList[] = { entranceKey , waterKey, closedWindow, openedWindow, jug, filledJug, lockedfaucet, faucet, fireplace, fireplaceOff, room3Key, room3Lock, waxFigure, room5Key, room5Lock,
	 stove, bellStick, bellBox, bell, room8Lock,note};
	addItems(itemList, 22);
	
	Room* frontHouse = new Room("Front House", FRONT_HOUSE , nullptr);
	Room* rightHouse = new Room("Right House", EAST_HOUSE, nullptr);
	Room* leftHouse = new Room("Left House", WEST_HOUSE, nullptr);
	Room* backHouse = new Room("Back House", BACK_HOUSE, nullptr);
	Room* entrance = new Room("House Entrance",HOUSE_ENTRANCE, entranceKey);
	Room* Room2 = new Room("Room2", ROOM2, nullptr);
	Room* Room3 = new Room("Room3", ROOM3, room3Key);
	Room* Room4 = new Room("Room4", ROOM4, nullptr);
	Room* Room5 = new Room("Room5", ROOM5, room5Key);
	Room* Room6 = new Room("Room6", ROOM6, nullptr);
	Room* Room7 = new Room("Room7", ROOM7, nullptr);
	Room* Room8 = new Room("Room8", ROOM8, bell);
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

	NPC* haemonculus = new NPC("Prisoner","A man dressed in rags restrained through 3 shackles.");
	listOfNPCs[haemonculus->entityName] = haemonculus;
	Room8->addNPC(haemonculus);

	//player->actualRoom = frontHouse;
	player->actualRoom = Room4;
	player->inventory.push_back(entranceKey);
	player->inventory.push_back(room5Key);
	cout<<player->actualRoom->entityDescription << endl;
	cout << endl;
	cout << endl;
	playerState = ROAMING_MODE;
	GameTime = clock();
}

void GameWorld::setPlayer(Player *p) {
	player = p;
}

void GameWorld::processInput(string input) {
	if (DEBUG_MODE) cout << "Processing input: " << input << endl;
	if (!input.empty()) {
		if (playerState == DIALOGUE_MODE) {
			if (dialoguingNPC != nullptr) { 
				if (!dialoguingNPC->checkAnswer(input)) {
					cout << "The shackles start to emit a strange energy... you feel weaker. You lost 5 points of life." << endl;
					cout << "You have " << player->playerUpdateHealth(5) << " out of 20." << endl;
					if (player->isPlayerDead()) {
						cout << TIMEUP_DEATH << endl;
						state = GAME_DEFEAT;
					}
				}
				if (dialoguingNPC->correctlyAnsweredAll()) { 
					dialoguingNPC->printEndDialogue();
					win();
				}
				else dialoguingNPC->printRiddle();
			}
		}
		else{
			vector<string> parameters;
			getParameters(input, &parameters);
			if (parameters.size() >= 1) {
				string command = parameters[0];
				if (command == "LOOK") {
					if (parameters.size() - 1 > 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
					else {
						if (parameters.size() == 1) LookTarget("this room");
						else LookTarget(parameters[1]);
					}
				}
				else if (command == "USE") {
					if (parameters.size() - 1 != 3) printNumberArgumentsError(3, ((int)parameters.size()) - 1);
					else UseItemWith(parameters[1], parameters[3]);
				}
				else if (command == "NORTH" || command == "SOUTH" || command == "EAST" || command == "WEST" || command == "UP" || command == "DOWN") {
					if (parameters.size() - 1 != 0) printNumberArgumentsError(0, ((int)parameters.size()) - 1);
					else MoveToDirection(parameters[0]);
				}
				else if (command == "OPEN") {
					if (parameters.size() - 1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
					else Open(parameters[1]);
				}
				else if (command == "TAKE") {
					if (parameters.size() - 1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
					else Take(parameters[1]);
				}
				else if (command == "DROP") {
					if (parameters.size() - 1 > 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
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
				else if (command == "TALK") {
					if (parameters.size() - 1 != 1) printNumberArgumentsError(1, ((int)parameters.size()) - 1);
					else Talk(parameters[1]);
				}
				else if (command == "TIME") {
					if (parameters.size() - 1 > 0) printNumberArgumentsError(0, ((int)parameters.size()) - 1);
					else Time();
				}
				else {
					cout << "Command not recognized" << endl;
				}
			}
			else cout << "Not enough arguments" << endl;
		}
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

void GameWorld::addItems(Item* list[], int size) {
	for (int i = 0; i < size; ++i) listOfItems.push_back(list[i]);
}

void GameWorld::addRooms(vector<Room*>(&rooms)) {
	for (int i = 0; i < 12; ++i) listOfRooms.push_back(rooms[i]);
}

void GameWorld::addExitsToRooms(string  exitlist[][6], int size) {
	for (int i = 0; i < size; ++i) listOfRooms[i]->setExits(exitlist[i]);
}

void GameWorld::openRoom(Item* key) {
	map<string, Room*>::iterator it = keyToRoom.find(key->entityName);
	if (it != keyToRoom.end()) {
		(*it).second->unlock(key);
		cout << "You unlocked the next room!" << endl;
	}
	else cout << "This key doesn't open the door." << endl;
}

void GameWorld::win() {
	cout << "You drink the antidote as fast as you can." << endl;
	cout << "Your body starts to stabilize and the poison inside your body is neutralized" << endl;
	cout << "You survived through this one by the skin of your teeth. Well played." << endl;
	state = GAME_VICTORY;
}

int GameWorld::checkState() {
	return state;
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



void GameWorld::LookTarget(string name) {
	if (DEBUG_MODE) cout << "Looking at: " + name << endl;
	list<Item*> *roomItems = &player->actualRoom->listOfItems;
	bool found = false;
	if (name == "me" || name == "myself") {
		cout << player->entityDescription << endl;
		found = true;
	}
	else if (name == "this room") {
		cout << player->actualRoom->entityDescription << endl;
		for (list<Item*>::iterator it = player->actualRoom->listOfItems.begin(); it != player->actualRoom->listOfItems.end(); ++it) {
			cout << "There's the item: " << (*it)->entityName << endl;
		}
		for (map<string, NPC*>::iterator it = player->getRoom()->listOfRoomNPCs.begin(); it != player->getRoom()->listOfRoomNPCs.end(); ++it) {
			cout << "There's someone: " << (*it).second->entityName << endl;
		}
		found = true;
	}
	else if (name == player->getRoom()->entityName) {
		cout << player->actualRoom->entityDescription << endl;
		found = true;
		if (!(*roomItems).empty()) {
			cout << "You see several things in the room:" << endl;
			for (list<Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end(); ++it) cout << "There's " << (*it)->entityDescription << endl;
		}
	}
	else if (!found) {
		map<string, NPC*>::iterator it = listOfNPCs.find(name);
		if (it != listOfNPCs.end()) {
			cout << (*it).second->entityDescription << endl;
			found = true;
		}
		if (!(*roomItems).empty() && !found) {
			for (list<Item*>::iterator it = (*roomItems).begin(); it != (*roomItems).end() && !found; ++it) {
				if ((*it)->entityName == name) {
					cout << (*it)->entityDescription << endl;
					found = true;
				}
			}
		}
		if (!found) {
			Item* inventoryItem = player->fetchItem(name);
			if (inventoryItem != nullptr) cout << inventoryItem->entityDescription << endl;
			found = true;
		}
		if (!found) cout << "I cannot find " << name << " to look at." << endl;
	}
}

void GameWorld::UseItemWith(string target1, std::string target2) {
	if (DEBUG_MODE) cout << "Using: " + target1 + " on " + target2 << endl;
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
				if (DEBUG_MODE) cout << "toBeCombined is: " << toBeCombined->entityName << " combinationItem is: " << combinationItem->entityName << endl;
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
			if (itemPair.first != nullptr) cout << "You only have " << itemPair.first->entityName << " but the other item is nowhere to be found in the room or your inventory." << endl;
			else if (itemPair.second != nullptr) cout << "You only have " << itemPair.second->entityName << " but the other item is nowhere to be found in the room or your inventory." << endl;
			else cout << "You have neither of those items." << endl;
		}
	}
	else cout << "I cannot use the item with itself." << endl;
}

void GameWorld::Open(string target) {
	if (DEBUG_MODE) cout << "Opening: " + target << endl;
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
	else {
		itemOfList = player->actualRoom->fetchItemFromRoom(target);
		if (itemOfList == nullptr) cout << "The item " << target << " is not here to be opened!" << endl;
		else {
			if (itemOfList->itemContained != nullptr) {
				opened = true;
			}
			else  cout << "The item " << target << " is empty!" << endl;
		}		
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
				//cout << "I should not be discarding this" << endl;
			}
			else {
				//player->actualRoom->listOfItems.remove(itemOfList);
				itemOfList->itemContained = nullptr;
				map<string,  Item*>::iterator it = replacements.find(itemOfList->entityName);
				if ( it != replacements.end()) {					
					player->actualRoom->listOfItems.remove(itemOfList);
					player->actualRoom->listOfItems.push_back((*it).second);
					replacements.erase(itemOfList->entityName);
				}
			}
		}
	}
}

void GameWorld::Take(string target) {
	if (DEBUG_MODE) cout << "Picking up: " + target << endl;
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
	if (DEBUG_MODE) cout << "Dropping: " + target << endl;
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
	if (DEBUG_MODE) cout << "Combining: " + target1 << " with "<<target2<< endl;
	Item* itemToPut = player->fetchItem(target1);
	if (itemToPut != nullptr) {
		Item* receivingItem = player->fetchItem(target2);
		if (receivingItem != nullptr && receivingItem->itemContained == nullptr) {
			if (receivingItem->entityName == "Metal_box") {
				receivingItem->putItem(itemToPut);
				player->removeItem(itemToPut);
				cout << "You put " << target1 << " inside Metal_box" << endl;
			}
			else if ((receivingItem->entityName == "Bell" && itemToPut->entityName == "Bell-clapper")) {
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
				player->removeItem(itemToPut);
				cout << "You put " << target1 << " inside " << target2<<" .";
			}
			else cout << "You cannot put " << target1 << " inside "<< target2 << endl;
		}
	}
	else cout << "No item: " << target1 << " found in inventory." << endl;
}

void GameWorld::CheckInventory() {
	list<Item*> inventory = player->inventory;
	for (list<Item*>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
		cout << (*it)->entityName << endl;
	}
}

void GameWorld::Talk(string target) {
	NPC* ptrNPC = player->getRoom()->fetchNPCFromRoom(target);
	if (ptrNPC!= nullptr) {
		playerState = DIALOGUE_MODE;
		dialoguingNPC = ptrNPC;
		dialoguingNPC->printIntro();
		dialoguingNPC->printRiddle();
	}
	else cout << "There's no " << target << " in the room." << endl;
}

void GameWorld::Time() {
	cout << clock() - GameTime / CLOCKS_PER_SEC << endl;

}

clock_t GameWorld::checkTime() {
	return  (clock()-GameTime) / CLOCKS_PER_SEC;
}