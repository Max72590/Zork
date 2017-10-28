#pragma once
#include "Entity.h"
#include <vector>
#include <string>

class Room;

class NPC :
	public Entity
{
public:
	NPC();
	NPC(std::string name, std::string desc);
	~NPC();

public:
	bool checkAnswer(std::string const response);
	void const printRiddle();
	void const printEndDialogue();
	int const getIndex();
	bool const correctlyAnsweredAll();
	void const printIntro();

private:
	int riddleIndex;
	std::vector<std::string> dialogueLines;
	std::vector<std::string> riddleOptions;
	std::vector<int> correctAnswers;

};

