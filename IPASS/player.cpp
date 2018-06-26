#include "player.hpp"

void player::draw(){
	w.write(hwlib::location(start_x, start_y), hwlib::black);
}

void player::clear(){
	w.write(hwlib::location(start_x, start_y), hwlib::white);
}

int player::getX(){
	return start_x;
}
int player::getY(){
	return start_y;
}
void player::shiftLeft(int value){
	start_x -= value;
}
void player::shiftRight(int value){
	start_x += value;
}
void player::shiftUp(int value){
	start_y -= value;
}
void player::shiftDown(int value){
	start_y += value;
}
