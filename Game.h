#ifndef GAME_H
#define GAME_H

#include "Theme.h"
#include "Types.h"
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
		void controlsCallback(int index);
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
		
		void initBoard();
		
		inline int wrap(int val) const { return (val + 11) % 11; }
		inline Position wrap(Position pos) const { return Position(wrap(pos.row), wrap(pos.col)); }

		bool areFriendly(Marker m1, Marker m2) const;
		bool areHostile(Marker m1, Marker m2) const;
		bool canPieceMove(Position pos) const;
		bool canPlayerMove(bool attacker) const;
		Marker getMarker(Position pos) const;
		
		
		void setMarker(Marker m, Position pos);
		void moveMarker(Position from, Position to);
		
		void tryEscape();
		void tryCapture(Position pos);
		void cleanupCorpses();
		
		void handleInput();
	    void handleSelectionInput(char c);
	    void handleMoveInput(char c);
	    void handleExitPromptInput(char c);
		void redrawBoard(const std::string& comment1 = "", const std::string& comment2 = "");
		
};

#endif

