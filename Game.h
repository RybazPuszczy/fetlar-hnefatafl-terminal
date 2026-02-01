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
		GameState gameState;
		Marker ** board;
		Theme * theme;
		TerminalRenderer * tr;
		Position indicatorPos = Position(0,0);
		Position selectedPos = Position(-1,-1);
		inline bool isSelectionEmpty() const { return selectedPos==Position(-1,-1); };
		bool attackerTurn = true;
		bool debugMode = false;
		
		int wrap(int val) const;
		void initBoard();
		void handleInput();
	    void handleSelectionInput(char c);
	    void handleMoveInput(char c);
	    void handleExitPromptInput(char c);
		void redrawBoard(const std::string& comment1 = "", const std::string& comment2 = "");
		
};

#endif

