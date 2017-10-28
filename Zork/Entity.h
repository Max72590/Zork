#pragma once

#include <string>

class Entity
{
public:
	Entity();
	~Entity();

public:

	Entity* parent = nullptr;
	std::string entityName;
	std::string entityDescription;
};

