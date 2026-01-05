#include "TerminalRenderer.h"

#include <iostream>
#include <windows.h>

#include "Types.h"
#include "Constants.h"
#include "Theme.h"

using namespace std;

// ============================== globals ==============================
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// ============================== members ==============================
void TerminalRenderer::clearScreen(){
	COORD cursorPosition = { 0,0 };
	SetConsoleCursorPosition(hConsole, cursorPosition);
}; // https://stackoverflow.com/questions/34842526/update-console-without-flickering-c

void TerminalRenderer::setColor(int color){ this->setColor(color, 0); }

void TerminalRenderer::setColor(int color, bool highlight){
	if(highlight) this->reverseHighlight(color);
	else SetConsoleTextAttribute(hConsole, Colors::BACKGROUND(color,highlight*Colors::DARKER(Colors::CYAN)));
}

void TerminalRenderer::reverseHighlight(int color){
	SetConsoleTextAttribute(hConsole, Colors::BACKGROUND(Colors::BLACK,color));
}

TerminalRenderer::TerminalRenderer() : 
	borderH('-'), borderV(':'), borderI('+'), 
	indicatorH('^'), indicatorV('<'), marginL("\t"), marginR("\t\t"),
	debug(false), theme(new Theme()) 
	{};

TerminalRenderer::TerminalRenderer(bool debug) : TerminalRenderer::TerminalRenderer(){
	this->debug = debug;
};

TerminalRenderer::TerminalRenderer(Theme * theme) : TerminalRenderer::TerminalRenderer(){
	this->theme = theme;
};

TerminalRenderer::TerminalRenderer(Theme * theme, bool debug) : TerminalRenderer::TerminalRenderer(){
	this->debug = debug;
	this->theme = theme;
};

TerminalRenderer::TerminalRenderer(
		char borderH, char borderV, char borderI, char indicatorH, 
		char indicatorV, string marginL, string marginR, Theme * theme, bool debug
	){
	this->borderH = borderH;
	this->borderV = borderV;
	this->borderI = borderI;
	this->indicatorH = indicatorH;
	this->indicatorV = indicatorV;
	this->marginL = marginL;
	this->marginR = marginR;
	this->debug = debug;
	this->theme = theme;
};

void TerminalRenderer::displayHorizontalIndicator(Position indicatorPos){
	cout << this->marginL;
	for(char col=0;col<11;col++){
		if(col==0) cout << " ";
		cout << " ";
		if(col==indicatorPos.col){
			setColor(theme->indicatorColor);
			cout << this->indicatorH;
			setColor(theme->defualtColor);
		}else{
			cout << ' ';
		}
		cout << "  "; 
	};
	cout << endl;
}

void TerminalRenderer::displayBorder(char row){
	cout << this->marginL;
	setColor(theme->borderColor);
	for(char col=0;col<11;col++){
		if(col==0) cout << this->borderI;
		cout << this->borderH << this->borderH << this->borderH << this->borderI;
	};
	setColor(this->theme->defualtColor);
	cout << this->marginR;
	if(this->debug) cout << "<- horizontal border " << (int)row; // debug 2k
	cout << endl;
};

void TerminalRenderer::displayFields(char row, Marker ** board, Position indicatorPos){
	cout << this->marginL;
	for(char col=0;col<11;col++){
		bool isFieldSelected = col==indicatorPos.col&&row==indicatorPos.row;
		if(col==0){
			setColor(theme->borderColor);
			cout << this->borderV;
		}
		setColor(this->theme->markerColors[board[row][col]],isFieldSelected);
		cout << " ";
		cout << board[row][col];
		cout << " ";
		setColor(theme->borderColor);
		cout << this->borderV;
		setColor(theme->defualtColor);
	};
	cout << " ";
	if(row==indicatorPos.row){
		setColor(theme->indicatorColor);
		cout << this->indicatorV;
	}else{
		cout << ' ';
	}
	setColor(theme->defualtColor);
	cout << this->marginR;
	if(this->debug) cout << "<- row " << (int)row; // debug 2k+1
	cout << endl;
};

void TerminalRenderer::displayBoard(Marker ** board, Position indicatorPos){
		for(char i=0;i<11;i++){
		
		if(i==0){
			// displayHorizontalIndicator(6,'v');
			displayBorder(i);
		};
		
		displayFields(i, board, indicatorPos);
		
		displayBorder(i+1);		
		if(i==10) displayHorizontalIndicator(indicatorPos);
		
	};	
};
