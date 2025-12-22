#include "TerminalRenderer.h"

#include <iostream>
#include <windows.h>

#include "Marker.h"
#include "Constants.h"
#include "Theme.h"

using namespace std;

// ============================== globals ==============================
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// ============================== members ==============================
void TerminalRenderer::setColor(char color){ this->setColor(color, 0); }

void TerminalRenderer::setColor(char color, bool highlight){
	if(highlight) this->reverseHighlight(color);
	else SetConsoleTextAttribute(hConsole, Colors::BACKGROUND(color,highlight*Colors::DARKER(Colors::CYAN)));
}

void TerminalRenderer::reverseHighlight(char color){
	SetConsoleTextAttribute(hConsole, Colors::BACKGROUND(Colors::BLACK,color));
}

TerminalRenderer::TerminalRenderer(){
	this->borderH = '-';
	this->borderV = ':';
	this->borderI = '+';
	this->indicatorH = '^';
	this->indicatorV = '<';
	this->marginL = "\t";
	this->marginR = "\t\t";
	this->debug = false;
	this->theme = new Theme();
};

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

void TerminalRenderer::displayHorizontalIndicator(char indicatorPos){
	cout << this->marginL;
	for(char j=0;j<11;j++){
		if(j==0) cout << " ";
		cout << " ";
		if(j==indicatorPos){
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
	for(char j=0;j<11;j++){
		if(j==0) cout << this->borderI;
		cout << this->borderH << this->borderH << this->borderH << this->borderI;
	};
	setColor(this->theme->defualtColor);
	cout << this->marginR;
	if(this->debug) cout << "<- intersection " << (int)row; // debug 2k
	cout << endl;
};

void TerminalRenderer::displayFields(char row, Marker ** board, char indicatorPos){
	cout << this->marginL;
	for(char j=0;j<11;j++){
		bool isFieldSelected = j==6&&row==4;
		if(j==0){
			setColor(theme->borderColor, 0);
			cout << this->borderV;
		}
		setColor(this->theme->markerColors[board[row][j]],isFieldSelected);
		cout << " ";
		cout << board[row][j];
		cout << " ";
		setColor(theme->borderColor);
		cout << this->borderV;
		setColor(theme->defualtColor);
	};
	cout << " ";
	if(row==indicatorPos){
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

void TerminalRenderer::displayBoard(Marker ** board){
		for(char i=0;i<11;i++){
		
		if(i==0){
			// displayHorizontalIndicator(6,'v');
			displayBorder(i);
		};
		
		displayFields(i, board, 4);
		
		displayBorder(i+1);		
		if(i==10) displayHorizontalIndicator(6);
		
	};	
};
