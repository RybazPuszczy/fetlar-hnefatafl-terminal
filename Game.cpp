#include "Game.h"
#include <windows.h>
#include <conio.h>

int Game::wrap(int val) const { return (val + 11) % 11; }

void Game::redrawBoard(const std::string& comment1, const std::string& comment2){
	this->tr->clearScreen();
	this->tr->displayBoard(comment1, comment2);
	Sleep(50);
}

void Game::debugCallback(int index){
	switch(index){
		case 0: std::cout << "indicatorPos: {" << this->indicatorPos.col << ", " << this->indicatorPos.row << "}"; break;
		case 1: std::cout << "selectedPos: {" << this->selectedPos.col << ", " << this->selectedPos.row << "}"; break;
		// ... Put some other debug values here
	};
	std::cout << "                           "; // to "clear" after a redraw
}

Game::Game(Theme* theme, bool debugMode) 
    : indicatorPos(Position(0,0)), attackerTurn(true), debugMode(debugMode), gameState(GameState::AwaitingSelection){

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

void Game::handleInput(){
	char c = getch();
	switch(this->gameState){
		case GameState::AwaitingSelection:
			this->handleSelectionInput(c);
			break;
		case GameState::AwaitingMove:
			this->handleMoveInput(c);
			break;
		case GameState::ExitPrompt:
			this->handleExitPromptInput(c);
    }
}

void Game::handleSelectionInput(char c){
	switch(c){
		case KEY_UP:
			this->indicatorPos.row = this->wrap(this->indicatorPos.row-1);
			redrawBoard();
			break;
        case KEY_DOWN:
			this->indicatorPos.row = this->wrap(this->indicatorPos.row+1);
			redrawBoard();
			break;
        case KEY_RIGHT:
			this->indicatorPos.col = this->wrap(this->indicatorPos.col+1);
			redrawBoard();
			break;
        case KEY_LEFT:
			this->indicatorPos.col = this->wrap(this->indicatorPos.col-1);
			redrawBoard();
			break;
        case ENTER:
        	this->selectedPos = this->indicatorPos;
        	this->gameState = GameState::AwaitingMove;
	        redrawBoard(
				std::string("Now it's ") + ((attackerTurn) ? "attackers'" : "defenders'") + " turn.",
				std::string("Selected: \"") + static_cast<char>(this->board[selectedPos.col][selectedPos.row]) + "\" at column " + std::to_string(this->selectedPos.col) + ", row " + std::to_string(this->selectedPos.row)
			);
        	break;
        case ESC:
//			this->gameState = GameState::Aborted;
			this->gameState = GameState::ExitPrompt;
			redrawBoard("","Are you sure you want to quit? (Y/N)");
			break;
	}
            
};
void Game::handleMoveInput(char c){
	switch(c){
		case KEY_UP:
			this->indicatorPos.col = this->selectedPos.col;
			this->indicatorPos.row = this->wrap(this->indicatorPos.row-1);
			redrawBoard();
            break;
        case KEY_DOWN:
			this->indicatorPos.col = this->selectedPos.col;
			this->indicatorPos.row = this->wrap(this->indicatorPos.row+1);
			redrawBoard();
            break;
        case KEY_RIGHT:
			this->indicatorPos.row = this->selectedPos.row;
			this->indicatorPos.col = this->wrap(this->indicatorPos.col+1);
			redrawBoard();
            break;
        case KEY_LEFT:
			this->indicatorPos.row = this->selectedPos.row;
			this->indicatorPos.col = this->wrap(this->indicatorPos.col-1);
			redrawBoard();
			break;
		case ENTER:
			{
			std::string comment2 = std::string("Moved: \"") + static_cast<char>(this->board[selectedPos.col][selectedPos.row]) + "\" to column " + std::to_string(this->indicatorPos.col) + ", row " + std::to_string(this->indicatorPos.row);
        	this->selectedPos = Position(-1,-1);
    		this->attackerTurn = !this->attackerTurn; 
			this->gameState = GameState::AwaitingSelection;
        	redrawBoard(
				std::string("Now it's ") + ((attackerTurn) ? "attackers'" : "defenders'") + " turn.",
				comment2
			);
			}
        	break;
        case ESC:
    		this->selectedPos = Position(-1,-1);
    		this->gameState = GameState::AwaitingSelection;
			redrawBoard();
    		break;
	}
};

void Game::handleExitPromptInput(char c){
	switch(c){
		case 'Y':
		case 'y':
		case ENTER:
			this->gameState=GameState::Aborted;
			break;
		case 'N':
		case 'n':
		case ESC:
			this->gameState=GameState::AwaitingSelection;
			this->redrawBoard(""," ");
			break;
	}
};

void Game::run(){
	redrawBoard();
	while(this->gameState!=GameState::Aborted)
    {
    	this->handleInput();
    }
}

Game::~Game(){
	delete[] theme;
	for(int i=0;i<11;i++) delete[] board[i];
	delete[] board;
}
