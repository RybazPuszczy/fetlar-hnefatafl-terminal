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
		Position indicatorPos;
		Position selectedPos;
		bool attackerTurn;
		bool debugMode;
		
		void initBoard();
		void getInput();
		void redrawBoard();
		
};

#endif

