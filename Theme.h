#ifndef THEME_H
#define THEME_H
#include <map>
#include "Types.h"
#include "Constants.h"
using namespace Colors;

struct Theme
{
	std::map<Marker, int> markerColors;
	
	int borderColor, indicatorColor, defualtColor;
	
	Theme(){
		this->markerColors[Marker::King] 		= YELLOW;
		this->markerColors[Marker::Defender]	= DARKER(this->markerColors[Marker::King]);
		this->markerColors[Marker::Attacker]	= DARKER(RED);
		this->markerColors[Marker::Empty]		= WHITE;
		this->markerColors[Marker::Throne]		= WHITE;
		this->markerColors[Marker::Corner]		= CYAN;
		this->markerColors[Marker::Wall]		= GRAY;
		this->markerColors[Marker::Captured]	= WHITE;		
		
		this->borderColor = GRAY;
		this->indicatorColor = WHITE;
		this->defualtColor = WHITE;
	}
};

#endif
