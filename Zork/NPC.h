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
	bool checkAnswer(std::string response);
	void printRiddle();
	void printEndDialogue();
	int getIndex();
	bool correctlyAnsweredAll();
	void printIntro();

private:
	int riddleIndex;
	std::vector<std::string> dialogueLines;
	std::vector<std::string> riddleOptions;
	std::vector<int> correctAnswers;

};

