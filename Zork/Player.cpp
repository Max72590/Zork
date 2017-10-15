#include "Player.h"
#include "GameWorld.h"

Player::Player()
{
	entityName = "Player";
	entityDescription = "It's just me.";
}


Player::~Player()
{
}

void Player::addItem(Item* item) {
	inventory.push_back(item);
}

void Player::removeItem(Item* item) {
	inventory.remove(item);
}

/*
void Player::MoveToDirection(std::string direction) {
	int roomIndex;
	if (direction == "NORTH") roomIndex = NORTH;
	if (direction == "NORTH") roomIndex = SOUTH;
	if (direction == "NORTH") roomIndex = EAST;
	if (direction == "NORTH") roomIndex = WEST;
	if (direction == "NORTH") roomIndex = UP;
	if (direction == "NORTH") roomIndex = DOWN;
	PrintMessage("Moving to direction: " + direction);
}

void Player::LookAt(std::string target) {
	PrintMessage("Looking at: " + target);
}

void Player::UseItem(std::string target1, std::string target2) {
	PrintMessage("Using: " + target1 + " on " + target2);

}

void Player::Open(std::string target) {
	PrintMessage("Opening: " + target);
}

void Player::Take(std::string target) {
	PrintMessage("Picking up: " + target);
}

void Player::Drop(std::string target) {
	PrintMessage("Dropping: " + target);
}*/