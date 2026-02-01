#include "Game.h"
#include <windows.h>
#include <conio.h>

int Game::wrap(int val) const { return (val + 11) % 11; }
Position Game::wrap(Position pos) const { return Position(wrap(pos.row), wrap(pos.col)); }

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

//void Game::moveMarkerToIndicator(){
//	this->board[this->indicatorPos.row][this->indicatorPos.col] = this->board[this->selectedPos.row][this->selectedPos.col];
//	this->board[this->selectedPos.row][this->selectedPos.col] = Marker::Empty;
//}

Marker Game::getMarker(Position pos){ 
	if(pos.row > 10 || pos.row < 0 || pos.col > 10 || pos.col < 0){
		return Marker::Edge;
	}
	return this->board[pos.row][pos.col]; 
}

void Game::setMarker(Marker m, Position pos){ this->board[pos.row][pos.col] = m; }

void Game::moveMarker(Position from, Position to){
	if(from==to) return;
	setMarker(getMarker(from),to);
	if(from == Position(5,5)) setMarker(Marker::Throne,from); else setMarker(Marker::Empty,from);
}

bool Game::areFriendly(Marker m1, Marker m2) const { return ( isAttacker(m1) && isAttacker(m2) || isDefender(m1) && isDefender(m2) ); }
// not being friendly nor hostile means being neutral.
bool Game::areHostile(Marker m1, Marker m2) const{ // for checking for captures
	return (
		isAttacker(m1) && isDefender(m2) 
		|| isDefender(m1) && isAttacker(m2) 
		|| (isRestricted(m1) xor isRestricted(m2)) && ( isPiece(m1)&&!isKing(m1) xor isPiece(m2)&&!isKing(m2) ) // edges, corners and throne are hostile and take part in captures too.
	);
}

void Game::tryCapture(Position pos){
	Position NESW[4] = {Position(-1,0), Position(0,1), Position(1,0), Position(0,-1)};
	for(int i=0; i<4; i++){
		if(this->attackerTurn && isKing(this->getMarker(pos+NESW[i]))){
			if(
				this->areHostile(this->getMarker(pos+NESW[i]), this->getMarker(pos+NESW[i]+NESW[0]))
				&& this->areHostile(this->getMarker(pos+NESW[i]), this->getMarker(pos+NESW[i]+NESW[1]))
				&& this->areHostile(this->getMarker(pos+NESW[i]), this->getMarker(pos+NESW[i]+NESW[2]))
				&& this->areHostile(this->getMarker(pos+NESW[i]), this->getMarker(pos+NESW[i]+NESW[3]))
			){
				this->gameState = GameState::Resolved;
				this->redrawBoard("THE KING HAS BEEN CAPTURED!","Attackers won!");
			}
		}else if(
			isPiece(this->getMarker(pos+NESW[i]))
			&& this->areHostile(this->getMarker(pos), this->getMarker(pos+NESW[i]))
			&& this->areHostile(this->getMarker(pos+NESW[i]), this->getMarker(pos+NESW[i]+NESW[i]))
		){
			setMarker(Marker::Captured, pos+NESW[i]);
		}
	}
}

void Game::cleanupCorpses(){
	for(int i=0;i<11;i++) for(int j=0;j<11;j++) if(this->board[i][j] == Marker::Captured) this->board[i][j] = Marker::Empty;
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
			this->indicatorPos = wrap(this->indicatorPos+Position(-1,0));
			redrawBoard();
			break;
        case KEY_DOWN:
			this->indicatorPos = wrap(this->indicatorPos+Position(1,0));
			redrawBoard();
			break;
        case KEY_RIGHT:
			this->indicatorPos = wrap(this->indicatorPos+Position(0,1));
			redrawBoard();
			break;
        case KEY_LEFT:
			this->indicatorPos = wrap(this->indicatorPos+Position(0,-1));
			redrawBoard();
			break;
        case ENTER:
        	if(
				! (isAttacker(this->getMarker(this->indicatorPos)) && this->attackerTurn)
				&& ! (isDefender(this->getMarker(this->indicatorPos)) && !this->attackerTurn)
			) break;
			
        	this->selectedPos = this->indicatorPos;
        	this->gameState = GameState::AwaitingMove;
	        redrawBoard(
				std::string("Selected: \"") + static_cast<char>(this->getMarker(this->selectedPos)) + "\" at column " + std::to_string(this->selectedPos.col) + ", row " + std::to_string(this->selectedPos.row),
				""
			);
        	break;
        case ESC:
			this->gameState = GameState::ExitPrompt;
			redrawBoard("","Are you sure you want to quit? (Y/N)");
			break;
	}
            
};
void Game::handleMoveInput(char c){
	switch(c){
		case KEY_UP:
			this->indicatorPos.col = this->selectedPos.col;
			this->indicatorPos = this->indicatorPos+Position(-1,0);
			this->redrawBoard();
            break;
        case KEY_DOWN:
			this->indicatorPos.col = this->selectedPos.col;
			this->indicatorPos = this->indicatorPos+Position(1,0);
			this->redrawBoard();
            break;
        case KEY_RIGHT:
			this->indicatorPos.row = this->selectedPos.row;
			this->indicatorPos = this->indicatorPos+Position(0,1);
			this->redrawBoard();
            break;
        case KEY_LEFT:
			this->indicatorPos.row = this->selectedPos.row;
			this->indicatorPos = this->indicatorPos+Position(0,-1);
			this->redrawBoard();
			break;
		case ENTER:
			{
			if(selectedPos==indicatorPos) break;
			
			std::string comment2 = std::string("Moved: \"") + static_cast<char>(this->getMarker(this->selectedPos)) + "\" to column " + std::to_string(this->indicatorPos.col) + ", row " + std::to_string(this->indicatorPos.row);
			this->cleanupCorpses();
			this->moveMarker(this->selectedPos,this->indicatorPos);
			this->tryCapture(this->indicatorPos);
    		if(this->gameState==GameState::Resolved) break;
        	this->selectedPos = Position(-1,-1);
    		this->attackerTurn = !this->attackerTurn; 
			this->gameState = GameState::AwaitingSelection;
        	this->redrawBoard(
				comment2,
				std::string("Now it's ") + ((attackerTurn) ? "attackers'" : "defenders'") + " turn."
			);
			}
        	break;
        case ESC:
    		this->selectedPos = Position(-1,-1);
    		this->gameState = GameState::AwaitingSelection;
			this->redrawBoard();
    		break;
	}
	//moves indicator back if move to the field is illegal. With sleep in redraw it makes a nice bounce-back effect.
	if(!(
		this->indicatorPos == this->selectedPos 
		|| isEmpty(this->getMarker(this->indicatorPos))
		|| isRestricted(this->getMarker(this->indicatorPos)) && isKing(this->getMarker(this->selectedPos))
	)) switch(c){
		case KEY_UP: handleMoveInput(KEY_DOWN); break;
		case KEY_DOWN: handleMoveInput(KEY_UP); break;
		case KEY_LEFT: handleMoveInput(KEY_RIGHT); break;
		case KEY_RIGHT: handleMoveInput(KEY_LEFT); break;
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
	redrawBoard("","The first move is attackers'.");
	while(this->gameState!=GameState::Aborted && this->gameState!=GameState::Resolved)
    {
    	this->handleInput();
    }

}

Game::~Game(){
	delete[] theme;
	for(int i=0;i<11;i++) delete[] board[i];
	delete[] board;
}
