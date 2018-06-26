#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "hwlib.hpp"

class player{
private:
	int start_x, start_y;
	hwlib::glcd_oled & w;
public:
	player(
		hwlib::glcd_oled & w, 
		int p_start_x, 
		int p_start_y
	):
		start_x( p_start_x ),
		start_y( p_start_y ),
		w( w )
	{}
	
	void draw();
	void clear();
	
	int getX();
	int getY();
	
	void shiftLeft(int value);
	void shiftRight(int value);
	void shiftUp(int value);
	void shiftDown(int value);
};

#endif // PLAYER_HPP
