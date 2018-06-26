#include "rectangle.hpp"

void rectangle::draw(){
	line top(w, start_x, start_y, end_x, start_y);
	line bottom(w, start_x, end_y, end_x, end_y);
	line left(w, start_x, start_y, start_x, end_y);
	line right(w, end_x, start_y, end_x, end_y);
	
	top.print();
	bottom.print();
	left.print();
	right.print();
}

void rectangle::clear(){
	for(int x = start_x; x <= end_x; x++){
		for(int y = start_y; y <= end_y; y++){
			w.write(hwlib::location(x, y), hwlib::white);
		}
	}
}
int rectangle::getStartX(){
	return start_x;
}
int rectangle::getStartY(){
	return start_y;
}
int rectangle::getEndX(){
	return end_x;
}
int rectangle::getEndY(){
	return end_y;
}
void rectangle::setStartX(int & value){
	start_x = value;
}
void rectangle::setStartY(int & value){
	start_y = value;
}
void rectangle::setEndX(int & value){
	end_x = value;
}
void rectangle::setEndY(int & value){
	end_y = value;
}

void rectangle::shiftLeft(int value){
	start_x -= value;
	end_x -= value;
}
void rectangle::shiftRight(int value){
	start_x += value;
	end_x += value;
}
void rectangle::shiftUp(int value){
	start_y -= value;
	end_y -= value;
}
void rectangle::shiftDown(int value){
	start_y += value;
	end_y += value;
}