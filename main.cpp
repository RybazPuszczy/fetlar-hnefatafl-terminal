#include <iostream>
#include <conio.h>
#include <windows.h>
#include "TerminalRenderer.h"
#include "Types.h"
#include "Constants.h"

using namespace std;


void drawBoard(TerminalRenderer * tr, Marker ** board, Position pos){
		system("cls");
		tr->displayBoard(board, pos);
		Sleep(50);
}

int main(int argc, char** argv) {
	
//	cout << endl << endl;
	
	Marker ** board;
	board = new Marker * [11];
	for(int i=0;i<11;i++){
		board[i] = new Marker[11];
		for(int j=0;j<11;j++){
			
			if(i==0 && j==0 || i==0 && j==10 || i==10 && j==0 || i==10 && j==10 )
			board[i][j] = Marker::Corner; else
			if(i==5 && j==5)
			board[i][j] = Marker::King; else
			if(
				( i==5 && (j==3 || j==7) ) ||
				( i>=4 && i<=6 && (j==4 || j==6) ) ||
				( i>=3 && i<=7 && (j==5) )
				
			)
			board[i][j] = Marker::Defender; else
			if(
				( i>=3 && i<=7 && (j==0 || j==10) ) ||
				( j>=3 && j<=7 && (i==0 || i==10) ) ||
				( j==5 && (i==1 || i==9) ) ||
				( i==5 && (j==1 || j==9) )
			)
			board[i][j] = Marker::Attacker; else
			board[i][j] = Marker::Empty;
		}
	}
	Theme * t = new Theme();	
	Position pos;
	TerminalRenderer * tr = new TerminalRenderer(t, true);
	drawBoard(tr, board, pos);

	char c = 0;
	while(c!=ENTER)
    {
        c = 0;
        c=getch();

        switch(c) {
        case KEY_UP:
			pos.row = ((pos.row+11)-1)%11;
			drawBoard(tr, board, pos);
            break;
        case KEY_DOWN:
			pos.row = ((pos.row+11)+1)%11;
			drawBoard(tr, board, pos);
            break;
        case KEY_RIGHT:
			pos.col = ((pos.col+11)+1)%11;
			drawBoard(tr, board, pos);
            break;
        case KEY_LEFT:
			pos.col = ((pos.col+11)-1)%11;
			drawBoard(tr, board, pos);
            break;
        case ENTER:
            break;
        }
    }
	
	
	return 0;
}
