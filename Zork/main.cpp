#include <iostream>
#include <string>
#include "conio.h"
#include "GameWorld.h"
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
	while (looping) {
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
	}
	cout << "Exited the game successfully." << endl;
	return 0;
}