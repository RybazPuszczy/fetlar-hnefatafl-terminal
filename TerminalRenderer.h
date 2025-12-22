#ifndef TERMINALRENDERER_H
#define TERMINALRENDERER_H
#include "Marker.h"
#include "Constants.h"
#include "Theme.h"

class TerminalRenderer
{
	private:
		char borderH, borderV, borderI, indicatorH, indicatorV;
		std::string marginL, marginR;
		bool debug;
		Theme * theme;
		void setColor(char color);
		void setColor(char color, bool highlight);
		void reverseHighlight(char color);
	public:
		TerminalRenderer();
		TerminalRenderer(Theme * theme);
		TerminalRenderer(bool debug);
		TerminalRenderer(Theme * theme, bool debug);
		TerminalRenderer(char borderH, char borderV, char borderI, char indicatorH, char indicatorV, std::string marginL, std::string marginR, Theme * theme, bool debug);
		void displayHorizontalIndicator(char indicatorPos);
		void displayBorder(char row);
		void displayFields(char row, Marker ** board, char indicatorPos);
		void displayBoard(Marker ** board);
};

#endif
