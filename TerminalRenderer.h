#ifndef TERMINALRENDERER_H
#define TERMINALRENDERER_H
#include "Marker.h"
#include "Constants.h"

class TerminalRenderer
{
	private:
		char borderH, borderV, borderI, indicatorH, indicatorV;
		std::string marginL, marginR;
		bool debug;
		void setColor(char color, bool highlight);
		void reverseHighlight(char color);
	public:
		TerminalRenderer();
		TerminalRenderer(bool debug);
		TerminalRenderer(char borderH, char borderV, char borderI, char indicatorH, char indicatorV, std::string marginL, std::string marginR, bool debug);
		void displayHorizontalIndicator(char indicatorPos);
		void displayBorder(char row);
		void displayFields(char row, Marker ** board, char indicatorPos);
		void displayBoard(Marker ** board);
};

#endif
