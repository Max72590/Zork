#pragma once

#include <string>

enum type {ROOM,ITEM};

class Entity
{
public:
	Entity();
	~Entity();
	void UpdateEntity();
	void UpdateParent(Entity * newParent);
	void PrintMessage(std::string message);

public:

	Entity* parent = nullptr;
	std::string entityName;
	std::string entityDescription;
};

