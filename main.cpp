#include <iostream>
#include <windows.h>
#include "Game.h"

using namespace std;


void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
    
}; // https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt

int main(int argc, char** argv) {
	
	
	HCURSOR hCursor = GetCursor();	
	ShowConsoleCursor(false);
	SetCursor(NULL);
	
	Game * game = new Game(nullptr, true);
	game->run();
		
	ShowConsoleCursor(true);
	SetCursor(hCursor);
	
	return 0;
}
