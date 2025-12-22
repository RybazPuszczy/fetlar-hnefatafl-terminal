#include "Board.h"

Board::Board()
{
	this->data = new Marker * [11];
	for(int i=0;i<11;i++){
		this->data[i] = new Marker[11];
		for(int j=0;j<11;j++){
			
			if(i==0 && j==0 || i==0 && j==10 || i==10 && j==0 || i==10 && j==10 )
			this->data[i][j] = Marker::Corner; else
			if(i==5 && j==5)
			this->data[i][j] = Marker::King; else
			if(
				( i==5 && (j==3 || j==7) ) ||
				( i>=4 && i<=6 && (j==4 || j==6) ) ||
				( i>=3 && i<=7 && (j==5) )
				
			)
			this->data[i][j] = Marker::Defender; else
			if(
				( i>=3 && i<=7 && (j==0 || j==10) ) ||
				( j>=3 && j<=7 && (i==0 || i==10) ) ||
				( j==5 && (i==1 || i==9) ) ||
				( i==5 && (j==1 || j==9) )
			)
			this->data[i][j] = Marker::Attacker; else
			this->data[i][j] = Marker::Empty;
		}
	}
}

Board::~Board()
{
}
