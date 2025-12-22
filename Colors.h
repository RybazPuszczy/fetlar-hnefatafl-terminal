#ifndef COLORS_H
#define COLORS_H

namespace Colors {
	const char BLACK	= 0;
    const char GRAY		= 8;
    const char BLUE		= 9;
    const char GREEN 	= 10;
    const char CYAN 	= 11;
    const char PINK		= 12;
    const char RED 		= 12;
    const char YELLOW	= 14;
	const char WHITE	= 15;
    const char BLUE_BG	= 16;
    const char GREEN_BG	= 32;
    const char CYAN_BG	= 48;
	
	inline char DARKER(char color){
		return color-8;
	};
	
	inline char BACKGROUND(char fg, char bg){
		return(fg + 16*(bg));
	};

};

#endif
