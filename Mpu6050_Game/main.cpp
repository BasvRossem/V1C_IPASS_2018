#include "hwlib.hpp"
#include "MPU6050.hpp"
#include "rectangle.hpp"
#include "line.hpp"
#include "player.hpp"

int randomInt(int max, auto & time, auto & mpu){
	srand(mpu.getGyroX());
	int value = rand() % max;
	return value;
}

void drawBorder(auto & oled){
	for(int i = 0; i < 128; i++)
	{
		oled.write(hwlib::location(i, 11), hwlib::black);
		oled.write(hwlib::location(i, 64 - 1), hwlib::black);
	}
	for(int j = 11; j < 64; j++)
	{
		oled.write(hwlib::location(0, j), hwlib::black);
		oled.write(hwlib::location(128 - 1, j), hwlib::black);
	}
}

void control(auto & mpu, auto & person){
	mpu.setAccel();
	int x = mpu.getAccelX();
	int y = mpu.getAccelY();
	if(x > 3000){
		person.shiftUp(1);
	} else if(x < -3000){
		person.shiftDown(1);
	}
	if(y > 3000){
		person.shiftLeft(1);
	} else if(y < -3000){
		person.shiftRight(1);
	}
}

bool checkIfFinished(auto & person, auto & goal){
	int x = person.getX();
	int y = person.getY();
	if(x >= goal.getStartX() && x <= goal.getEndX() && y >= goal.getStartY() && y <= goal.getEndY()){
		return true;
	} else{
		return false;
	}
}

rectangle createGoal(auto & oled, auto & time, auto & mpu){
	int goalStartX = randomInt(100, time, mpu);
	int goalStartY = randomInt(40, time, mpu);
	if(goalStartX < 2){
		goalStartX = 2;
	}
	if(goalStartX > 110){
		goalStartX = 110;
	}
	if(goalStartY < 12){
		goalStartY = 12;
	}
	if(goalStartY > 50){
		goalStartY = 50;
	}
	int goalEndX = goalStartX + 10;
	int goalEndY = goalStartY + 10;
	return rectangle(oled, goalStartX, goalStartY, goalEndX, goalEndY);
}

void drawTime(auto & time, auto & oled){
	for(int x = 0; x < 100; x++){
		for(int y = 0; y < 10; y++){
			oled.write(hwlib::location(x, y), hwlib::black);
		}
	}
}

void reduceTime(auto & time, auto & oled){
	int value = time / 2.5;
	for(int y = 0; y < 11; y ++){
		oled.write(hwlib::location(value, y), hwlib::white);
	}
}

void newGame(auto & oled, auto & time, auto & mpu, auto & gameOver, auto & score, auto & scoreDisplay,  auto & font){
	mpu.setGyro();
	auto goal = createGoal(oled, time, mpu);
	auto person = player(oled, 64,32);
	goal.draw();
	scoreDisplay << "\f" << score << hwlib::flush;
	for(;;){
		reduceTime(time, oled);
		person.draw();
		hwlib::wait_ms(20);
		person.clear(); 
		control(mpu, person);
		if(checkIfFinished(person, goal)){
			score += 1;
			break;
		}
		if(time == 0){
			gameOver = true;
			break;
		}
		
		time -= 1;
	}
	person.clear();
	goal.clear();
}

int main( void ){
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	namespace target = hwlib::target;
	
	//Oled
	auto sclOled = target::pin_oc( target::pins::scl1 );
	auto sdaOled = target::pin_oc( target::pins::sda1 );
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( sclOled, sdaOled );
	auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );  
	
	//Gyroscope MPU6050
	auto sclGyro = target::pin_oc(target::pins::scl);
	auto sdaGyro = target::pin_oc(target::pins::sda);
	auto i2c_bus_Mpu6050 = hwlib::i2c_bus_bit_banged_scl_sda(sclGyro, sdaGyro);
	auto mpu = MPU6050(i2c_bus_Mpu6050); 
	mpu.wakeUp();
	hwlib::wait_ms(250);
	auto timePart = hwlib::window_part( 
		oled, 
		hwlib::location( 0, 0),
		hwlib::location( 64, 10));
	auto scorePart = hwlib::window_part( 
		oled, 
		hwlib::location( 106, 0 ),
		hwlib::location( 128, 10));
		
	auto font = hwlib::font_default_8x8();
	auto timeDisplay = hwlib::window_ostream( timePart, font );
	auto scoreDisplay = hwlib::window_ostream( scorePart, font );
	unsigned int time = 250;
	unsigned int score = 0;
	bool gameOver = false;
	oled.clear();
	drawBorder(oled);
	drawTime(time, oled);
	for(;;){
		newGame(oled, time, mpu, gameOver, score, scoreDisplay, font);
		if(gameOver){
			break;
		}
	}
	
	oled.clear();
	auto display= hwlib::window_ostream( oled, font );
	for(;;){
		display << "\t0007" << "Game Over" << hwlib::flush; 
		hwlib::wait_ms(1000);
		display << "\t0007" << "           "<< hwlib::flush;
		display << "\t0007" << "Score: "<< score << hwlib::flush;
		hwlib::wait_ms(1000);
		display << "\t0007" << "           "<< hwlib::flush;
	}
}
