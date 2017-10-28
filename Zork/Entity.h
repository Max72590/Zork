#ifndef __Entity__
#define __Entity__

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

#endif //__Entity__