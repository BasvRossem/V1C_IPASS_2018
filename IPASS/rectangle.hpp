#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "line.hpp"

class rectangle{
private:
	int start_x, start_y, end_x, end_y;
	hwlib::glcd_oled & w;
public:
	rectangle(
		hwlib::glcd_oled & w, 
		int p_start_x, 
		int p_start_y, 
		int p_end_x, 
		int p_end_y
	):
		start_x( p_start_x ),
		start_y( p_start_y ),
		end_x( p_end_x ),
		end_y( p_end_y ),
		w( w )
	{}
	void draw();
	void clear();
	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();
	
	void setStartX(int & value);
	void setStartY(int & value);
	void setEndX(int & value);
	void setEndY(int & value);
	
	void shiftLeft(int value);
	void shiftRight(int value);
	void shiftUp(int value);
	void shiftDown(int value);
};

#endif // RECTANGLE_HPP
