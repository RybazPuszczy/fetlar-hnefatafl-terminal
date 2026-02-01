#ifndef TERMINALRENDERER_H
#define TERMINALRENDERER_H
#include "Types.h"
#include "Constants.h"
#include "Theme.h"
#include <functional>

class TerminalRenderer
{
	private:
		// Symbols
		char 
			borderH = '-',
			borderV = ':',
			borderI = '+',
			indicatorH = '^',
			indicatorV = '<';
		std::string 
			marginL = "\t",
			marginR = "\t\t";
		
		bool debug = false;
		Theme * theme = nullptr;
		
		// game state refs		
		Marker ** boardRef = nullptr;
		const Position * indicatorPosRef = nullptr;
		const Position * selectedPosRef = nullptr;
		const bool * attackerTurnRef = nullptr;
		std::function<void(int)> debugCallbackRef;
		
		void setColor(int color);
		void setColor(int color, bool highlight);
		void reverseHighlight(int color);
		void displayHorizontalIndicator();
		void displayBorder(char row);
		void displayFields(char row);
	
	public:
		void setRefs(Marker ** board, const Position * indicatorPos, const Position * selectedPos, const bool * attackerTurn, std::function<void(int)>& debugCallback);
		
		TerminalRenderer(Theme * theme = nullptr, bool debug = false);
		TerminalRenderer(bool debug);
		
		TerminalRenderer(char borderH, char borderV, char borderI, char indicatorH, char indicatorV, 
							const std::string& marginL, const std::string& marginR, Theme * theme = nullptr, bool debug = false);
		void clearScreen();
		void displayBoard(const std::string& comment1, const std::string& comment2);
};

#endif
