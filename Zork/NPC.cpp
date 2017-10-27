#include "NPC.h"
#include "Globals.h"
#include "GameStrings.h"
using namespace std;


NPC::NPC()
{
}

NPC::NPC(std::string name, std::string desc) {
	entityName = name;
	entityDescription = desc;
	riddleIndex = 0;
	vector<int> answers{2,3,2};
	correctAnswers = answers;
	vector<string> lines{RIDDLE_1,RIDDLE_2,RIDDLE_3};
	dialogueLines = lines;
	vector<string> options{ RIDDLE_1_RESPONSES,RIDDLE_2_RESPONSES,RIDDLE_3_RESPONSES };
	riddleOptions = options;
}

NPC::~NPC()
{
}

void NPC::printRiddle() {
	if (riddleIndex < (int)dialogueLines.size()) {
		cout << dialogueLines[riddleIndex] << endl;
		cout << riddleOptions[riddleIndex] << endl;
	}
}

bool NPC::checkAnswer(string response) {
	if (response >= "1" && response <= "3") {
		int responseIndex = atoi(response.c_str());
		if (responseIndex == correctAnswers[riddleIndex%2]) {
			cout << "Heheheh... Correct!" << endl;			
			if (riddleIndex > 0) cout << "You see another of the shackles unlock and fall down to the floor." << endl;
			else  cout << "You see one of the shackles unlock and fall down to the floor." << endl;
			++riddleIndex;
			return true;
		}
		else { 
			cout << "WRONG!" << endl;
			return false;
		}
	}
	else cout << "You didn't select an actual answer" << endl;
	return true;
}

void NPC::printEndDialogue() {
	cout << END_DIALOGUE << endl;
}

int NPC::getIndex() {
	return riddleIndex;
}

bool NPC::correctlyAnsweredAll() {
	return riddleIndex > 2;
}

void NPC::printIntro() {
	cout << NPC_INTRO << endl;
	cout << endl;
	cout << NPC_RIDDLE_START << endl;
	cout << endl;
}