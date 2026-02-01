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

TerminalRenderer::TerminalRenderer(Theme * theme){
	this->theme = (theme!=nullptr)? theme : new Theme();
}	

TerminalRenderer::TerminalRenderer(
		char borderH, char borderV, char borderI, 
		char indicatorH, char indicatorV, 
		const string& marginL, const string& marginR, 
		Theme * theme
	) 
	: borderH(borderH), borderV(borderV), borderI(borderI), 
	indicatorH(indicatorH), indicatorV(indicatorV), 
	  marginL(marginL), marginR(marginR) {
	this->theme = (theme != nullptr) ? theme : new Theme();
}

void TerminalRenderer::displayHorizontalIndicator(){
	cout << this->marginL;
	for(char col=0;col<11;col++){
		if(col==0) cout << " ";
		cout << " ";
		if(col==this->indicatorPosRef->col){
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
	if(this->rightsideCallbackRef) this->rightsideCallbackRef(2 * row);
	cout << endl;
};

void TerminalRenderer::displayFields(char row){
	cout << this->marginL;
	for(char col=0;col<11;col++){
		bool isFieldIndicated = col==this->indicatorPosRef->col &&row==this->indicatorPosRef->row;
		bool isFieldSelected = col==this->selectedPosRef->col &&row==this->selectedPosRef->row;
		if(col==0){
			setColor(theme->borderColor);
			cout << this->borderV;
		}
		if(isEmpty(this->boardRef[row][col])){		
			setColor(this->theme->markerColors[(*this->attackerTurnRef)? Marker::Attacker : Marker::Defender], isFieldIndicated || isFieldSelected);
		}else{
			setColor(this->theme->markerColors[this->boardRef[row][col]], isFieldIndicated || isFieldSelected);
		}
		cout << " ";
		cout << this->boardRef[row][col];
		cout << " ";
		setColor(theme->borderColor);
		cout << this->borderV;
		setColor(theme->defualtColor);
	};
	cout << " ";
	if(row==this->indicatorPosRef->row){
		setColor(theme->indicatorColor);
		cout << this->indicatorV;
	}else{
		cout << ' ';
	}
	setColor(theme->defualtColor);
	cout << this->marginR;
	if(this->rightsideCallbackRef) this->rightsideCallbackRef(2*row + 1);
	cout << endl;
};

void TerminalRenderer::displayBoard(const string& comment1, const string& comment2){
	for(char i=0;i<11;i++){
	
		if(i==0) displayBorder(i);

		displayFields(i);
	
		displayBorder(i+1);		

		if(i==10) displayHorizontalIndicator();	
	};	
	
	if(!comment1.empty()){
		cout << "                                                           \r"
			<< comment1;
	}
	cout << "\n";
	if(!comment2.empty()){
		cout << "                                                           \r"
			<< comment2;
	}
	cout << "\n";		
};

void TerminalRenderer::setRefs(Marker ** board, const Position * indicatorPos, const Position * selectedPos, const bool * attackerTurn){
	this->boardRef = board;
	this->indicatorPosRef = indicatorPos;
	this->selectedPosRef = selectedPos;
	this->attackerTurnRef = attackerTurn;
}

void TerminalRenderer::setRefs(Marker ** board, const Position * indicatorPos, const Position * selectedPos, const bool * attackerTurn, std::function<void(int)>& rightsideCallback){
	this->setRefs(board, indicatorPos, selectedPos, attackerTurn);
	this->rightsideCallbackRef = rightsideCallback;
}

TerminalRenderer::~TerminalRenderer() {
    delete theme;
}
