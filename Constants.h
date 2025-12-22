#ifndef CONSTANTS_H
#define CONSTANTS_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define ESC 27

namespace Colors {
	const char BLACK	= 0;
    const char GRAY		= 8;
    const char BLUE		= 9;
    const char GREEN 	= 10;
    const char CYAN 	= 11;
    const char RED 		= 12;
    const char PINK		= 13;
    const char YELLOW	= 14;
	const char WHITE	= 15;
	
	inline constexpr DARKER(char color){ return (color>=8?color-8:color); };
	
	inline constexpr BACKGROUND(char fg, char bg){ return (fg + 16*(bg)); };
};

#endif
