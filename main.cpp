#include <iostream>
#include "TerminalRenderer.h"
#include "Marker.h"

using namespace std;

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
	bool debug = true;
//	cin >> debug;
	TerminalRenderer * tr = new TerminalRenderer(debug);
	tr->displayBoard(board);
	
	system("pause");
	return 0;
}
