
#include "conio.h"
#include "GameWorld.h"
#include "Globals.h"
#include "Player.h"

using namespace std;



int main() {
	GameWorld gm = GameWorld();
	Player p = Player();
	gm.setPlayer( &p);
	gm.initGameWorld();
	string input;
	char inputChar;
	bool looping = true;
	bool halfTimePassed = false;
	int gameState = KEEP_LOOPING;
	while (looping) {
		gameState = gm.checkState();
		if (gm.hasPlayerEnteredHouse()) {
			if ((float)(gm.checkTime() > (TOTAL_GAME_TIME / 2)) && !halfTimePassed) {
				halfTimePassed = true;
				cout << HALF_TIME_REMAINING << endl;
			}
			else if ((float)(gm.checkTime() > TOTAL_GAME_TIME) && halfTimePassed) {
				cout << TIMEUP_DEATH << endl;
				gameState = GAME_DEFEAT;
			}
		}
		switch (gameState) {
		case KEEP_LOOPING:
			if (_kbhit()) {
				inputChar = _getch();
				if (inputChar == '\r') {
					cout << endl;
					cout << endl;
					cout << endl;
					gm.processInput(input);
					input.clear();
					cout << endl;
					cout << endl;
				}
				else if (inputChar == '\b') {
					if (input.size() > 0) {
						input.pop_back();
						cout << inputChar;
						cout << " ";
						cout << inputChar;
					}
				}
				else {
					cout << inputChar;
					input = input + inputChar;
				}
			}
			break;
		
		case GAME_VICTORY:
			looping = false;
			break;
		case GAME_DEFEAT:
			looping = false;
			break;
		}
			
	}
	cout << "Exited the game successfully." << endl;
	system("pause");
	return 0;
}