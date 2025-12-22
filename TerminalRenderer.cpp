#include "TerminalRenderer.h"

#include <iostream>
#include <windows.h>

#include "Marker.h"
#include "Constants.h"

using namespace std;

// ============================== globals ==============================
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// ============================== members ==============================
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
};

TerminalRenderer::TerminalRenderer(bool debug) : TerminalRenderer::TerminalRenderer(){
	this->debug = debug;
};

TerminalRenderer::TerminalRenderer(
		char borderH, char borderV, char borderI, char indicatorH, 
		char indicatorV, string marginL, string marginR, bool debug
	){
	this->borderH = borderH;
	this->borderV = borderV;
	this->borderI = borderI;
	this->indicatorH = indicatorH;
	this->indicatorV = indicatorV;
	this->marginL = marginL;
	this->marginR = marginR;
	this->debug = debug;
};

void TerminalRenderer::displayHorizontalIndicator(char indicatorPos){
	cout << this->marginL;
	for(char j=0;j<11;j++){
		if(j==0) cout << " ";
		cout << " " << ((j==indicatorPos)?this->indicatorH:' ') << "  "; 
	};
	cout << endl;
}

void TerminalRenderer::displayBorder(char row){
	cout << this->marginL;
	setColor(Colors::GRAY, 0);
	for(char j=0;j<11;j++){
		if(j==0) cout << this->borderI;
		cout << this->borderH << this->borderH << this->borderH << this->borderI;
	};
	setColor(Colors::WHITE, 0);
	cout << this->marginR;
	if(this->debug) cout << "<- intersection " << (int)row; // debug 2k
	cout << endl;
};

void TerminalRenderer::displayFields(char row, Marker ** board, char indicatorPos){
	cout << this->marginL;
	for(char j=0;j<11;j++){
		bool isFieldSelected = j==6&&row==4;
		if(j==0){
			setColor(Colors::GRAY, 0);
			cout << this->borderV;
		}
		setColor(Colors::WHITE, isFieldSelected);
		
		switch(board[row][j]){
			case Marker::King:
				setColor(Colors::YELLOW, isFieldSelected);
				break;
			case Marker::Defender:
				setColor(Colors::DARKER(Colors::YELLOW), isFieldSelected);					
				break;
			case Marker::Attacker:
				setColor(Colors::DARKER(Colors::RED), isFieldSelected);					
				break;
			case Marker::Throne:
				setColor(Colors::WHITE, isFieldSelected);					
				break;
			case Marker::Corner:
				setColor(Colors::CYAN, isFieldSelected);					
				break;
			default:
				setColor(Colors::WHITE, isFieldSelected);
		}
		cout << " ";
		cout << board[row][j];
		cout << " ";
		setColor(Colors::GRAY, 0);
		cout << this->borderV;
		setColor(Colors::WHITE, 0);
	};
	cout << " " << ((row==indicatorPos)?this->indicatorV:' ') << this->marginR;
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
