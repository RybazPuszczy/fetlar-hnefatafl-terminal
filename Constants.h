#ifndef CONSTANTS_H
#define CONSTANTS_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESC 27

namespace Colors {
	const int BLACK		= 0;
    const int GRAY		= 8;
    const int BLUE		= 9;
    const int GREEN 	= 10;
    const int CYAN 		= 11;
    const int RED 		= 12;
    const int PINK		= 13;
    const int YELLOW	= 14;
	const int WHITE		= 15;
	
	inline constexpr int DARKER(int color){ return (color>=8?color-8:color); }; 
	
	inline constexpr int BACKGROUND(int fg, int bg){ return (fg + 16*(bg)); };
};

#endif
