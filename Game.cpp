#include "Game.h"
#include <windows.h>
#include <conio.h>

void Game::redrawBoard(){
	this->tr->clearScreen();
	this->tr->displayBoard();
	Sleep(50);
}

void Game::debugCallback(int index){
	switch(index){
		case 0: std::cout << "indicatorPos: {" << this->indicatorPos.col << ", " << this->indicatorPos.row << "}"; break;
		case 1: std::cout << "selectedPos: {" << this->selectedPos.col << ", " << this->selectedPos.row << "}"; break;
		// ... Put some other debug values here
	};
	std::cout << "                           "; // to "clear" after redraw
}

Game::Game(Theme* theme, bool debugMode) 
    : indicatorPos(Position(0,0)), attackerTurn(true), debugMode(debugMode){

	this->theme = (theme!=nullptr) ? theme : new Theme();
    this->tr = new TerminalRenderer(this->debugMode);
    
    std::function<void(int)> callbackRef = nullptr;
    
    if(this->debugMode) callbackRef = [this](int index) { this->debugCallback(index); };
    
    initBoard();
    
    this->tr->setRefs(this->board, &this->indicatorPos, &this->selectedPos, &this->attackerTurn, callbackRef);
}

void Game::initBoard(){
	
	this->board = new Marker * [11];
	
	for(int i=0;i<11;i++){
		this->board[i] = new Marker[11];
		for(int j=0;j<11;j++){
			
			if(i==0 && j==0 || i==0 && j==10 || i==10 && j==0 || i==10 && j==10 )
			this->board[i][j] = Marker::Corner; else
			if(i==5 && j==5)
			this->board[i][j] = Marker::King; else
			if(
				( i==5 && (j==3 || j==7) ) ||
				( i>=4 && i<=6 && (j==4 || j==6) ) ||
				( i>=3 && i<=7 && (j==5) )
				
			)
			this->board[i][j] = Marker::Defender; else
			if(
				( i>=3 && i<=7 && (j==0 || j==10) ) ||
				( j>=3 && j<=7 && (i==0 || i==10) ) ||
				( j==5 && (i==1 || i==9) ) ||
				( i==5 && (j==1 || j==9) )
			)
			this->board[i][j] = Marker::Attacker; else
			this->board[i][j] = Marker::Empty;
		}
	}
}

void Game::run(){
	redrawBoard();
	char c = 0;
	while(c!=ESC)
    {
        c = 0;
        c=getch();

        switch(c) {
        case KEY_UP:
			this->indicatorPos.row = ((this->indicatorPos.row+11)-1)%11;
			redrawBoard();
            break;
        case KEY_DOWN:
			this->indicatorPos.row = ((this->indicatorPos.row+11)+1)%11;
			redrawBoard();
            break;
        case KEY_RIGHT:
			this->indicatorPos.col = ((this->indicatorPos.col+11)+1)%11;
			redrawBoard();
            break;
        case KEY_LEFT:
			this->indicatorPos.col = ((this->indicatorPos.col+11)-1)%11;
			redrawBoard();
            break;
        case ENTER:
        	if(this->isSelectionEmpty()){
	        	this->selectedPos = this->indicatorPos;
	        	std::cout << "Selected: \"" << this->board[selectedPos.col][selectedPos.row] << "\" at column " << this->selectedPos.col << ", row " << this->selectedPos.row << "\t\t\n"; 
			}else{				
	        	std::cout << "Moved: \"" << this->board[selectedPos.col][selectedPos.row] << "\" to column " << this->indicatorPos.col << ", row " << this->indicatorPos.row << "\t\t\n"; 
	        	this->selectedPos= Position(-1,-1);
        		this->attackerTurn = !this->attackerTurn;
			}
        	std::cout << "Now it's " << ((attackerTurn) ? "attackers'" : "defenders'") << " turn."; 
        	redrawBoard();
            break;
        case ESC:
        	if(!this->isSelectionEmpty()) {
        		this->selectedPos= Position(-1,-1);
        		c = 0;
        		redrawBoard();
			}
        	break;
        }
    }
}

Game::~Game(){
	delete[] theme;
	for(int i=0;i<11;i++) delete[] board[i];
	delete[] board;
}
