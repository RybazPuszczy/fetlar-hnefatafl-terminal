#ifndef GAME_H
#define GAME_H

#include "Theme.h"
#include "TerminalRenderer.h"

#include <functional>

class Game
{
	public:
		Game(Theme * theme = nullptr, bool debugMode = false);
		~Game();
		void run();
		void debugCallback(int index);
	private:
		Marker ** board;
		Theme * theme;
		TerminalRenderer * tr;
		Position indicatorPos = { 0, 0 };
		Position selectedPos = {-1, -1};
		bool attackerTurn = true;
		bool debugMode = false;
		
		void initBoard();
		void getInput();
		void redrawBoard();
		
};

#endif

