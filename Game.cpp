#include "Game.h"
#include <windows.h>
#include <conio.h>


void Game::redrawBoard(){
	this->tr->clearScreen();
	this->tr->displayBoard(this->board, this->indicatorPos);
	Sleep(50);
}

Game::Game(Theme* theme, bool debugMode) 
    : indicatorPos({0,0}), attackerTurn(true), debugMode(debugMode){

	this->theme = (theme!=nullptr) ? theme : new Theme();
    this->tr = new TerminalRenderer(this->debugMode);
    initBoard();
    
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
        	this->selectedPos = this->indicatorPos;
        	redrawBoard();
        	std::cout << "Selected: \"" << this->board[selectedPos.col][selectedPos.row] << "\" at column " << this->selectedPos.col << ", row " << this->selectedPos.row << "  "; 
            break;
        case ESC:
        	break;
        }
    }
}

Game::~Game(){
	delete[] theme;
	for(int i=0;i<11;i++) delete[] board[i];
	delete[] board;
}
