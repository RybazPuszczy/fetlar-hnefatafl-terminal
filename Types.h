#ifndef MARKERS_H
#define MARKERS_H
#include <iostream>

enum class GameState {
	AwaitingSelection,
	AwaitingMove,
	ExitPrompt,
	Aborted,
	Resolved
};

enum class Marker : char {
	King 	= 'K',
	Defender = 'd', // or 2 displays a ":)" (at least in my terminal)
	Attacker = 'a',
	Empty = ' ',
	Throne = '#',
    Corner  = '~',
    Wall  = 'W'
};

inline bool isAttacker(Marker m) { return m == Marker::Attacker; }

inline bool isDefender(Marker m) { return m == Marker::King || m == Marker::Defender; }

inline bool isPiece(Marker m) { return isAttacker(m) || isDefender(m); }

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
