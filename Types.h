#ifndef MARKERS_H
#define MARKERS_H
#include <iostream>

enum class GameState {
	AwaitingSelection,
	AwaitingMove,
	ExitPrompt,
	ResetPrompt,
	Reset,
	Aborted,
	Resolved
};

enum class Marker : char {
	King 	= 'K',
	Defender = 'd', // or 2 displays a ":)" (at least in my terminal (indeed not everywhere...))
	Attacker = 'a',
	Empty = ' ',
	Throne = '#',
    Corner  = '~',
    Edge  = 'E',
    Captured = '.'
};

inline bool isAttacker(Marker m) { return m == Marker::Attacker; }

inline bool isDefender(Marker m) { return m == Marker::King || m == Marker::Defender; }

inline bool isKing(Marker m) { return m == Marker::King; }

inline bool isRestricted(Marker m) { return m == Marker::Throne || m == Marker::Corner; } //true for markers marking king-only fields.

inline bool isPiece(Marker m) { return isAttacker(m) || isDefender(m); }

inline bool isEmpty(Marker m) { return m == Marker::Empty || m == Marker::Captured; }

inline bool canEnter(Marker who, Marker where){	return isEmpty(where) || isRestricted(where) && isKing(who); } 

inline std::ostream& operator<<(std::ostream& os, Marker m) {
    return os << static_cast<char>(m);
}

struct Position {
    int row;
    int col;

    Position(int r = 0, int c = 0) : row(r), col(c) {}
    
	bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
    
   	Position operator+(const Position& other) const {
        return Position(this->row+other.row, this->col+other.col);
    }

    Position operator-(const Position& other) const {
        return Position(this->row-other.row, this->col-other.col);
    }
    
};

#endif 
