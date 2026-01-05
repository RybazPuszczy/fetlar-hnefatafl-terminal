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
	protected:
		void debugCallback(int index);
	private:
		Marker ** board;
		Theme * theme;
		TerminalRenderer * tr;
		Position indicatorPos = Position(0,0);
		Position selectedPos = Position(-1,-1);
		inline bool isSelectionEmpty() const { return selectedPos==Position(-1,-1); };
		bool attackerTurn = true;
		bool debugMode = false;
		
		void initBoard();
		void getInput();
		void redrawBoard();
		
};

#endif

