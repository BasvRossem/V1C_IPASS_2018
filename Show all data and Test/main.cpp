#include "hwlib.hpp"
#include "MPU6050.hpp"
//#include "MPU6050_test.cpp"


bool between(int16_t value, int  min, int  max){
	if(value > min && value < max){
		return true;
	} else{
		return false;
	}
}

bool testWhoAmI(auto & mpu){
	if(mpu.whoAmI() == 104){
		return true;
	} else{
		return false;
	}
}

bool testAccel(auto & mpu){
	int16_t accelx = mpu.getAccelX();
	int16_t accely = mpu.getAccelY();
	int16_t accelz = mpu.getAccelZ();
	bool x = between(accelx, -1000, 1000);
	bool y = between(accely, -1000, 1000);
	bool z = between(accelz, 17000, 19000);
	if(x && y && z){
		return true;
	} else {
		if(x == 0){
			hwlib::cout << "Accel x failed\n";
		}
		if(y == 0){
			hwlib::cout << "Accel y failed\n";
		}
		if(z == 0){
			hwlib::cout << "Accel z failed\n";
		}
		return false;
	}
}

bool testGyro(auto & mpu){
	int16_t gyrox = mpu.getGyroX();
	int16_t gyroy = mpu.getGyroY();
	int16_t gyroz = mpu.getGyroZ();
	bool x = between(gyrox, -200, 200);
	bool y = between(gyroy, -200, 200);
	bool z = between(gyroz, -200, 200);
	if(x && y && z){
		return true;
	} else {
		if(x == 0){
			hwlib::cout << "Gyro x failed\n";
		}
		if(y == 0){
			hwlib::cout << "Gyro y failed\n";
		}
		if(z == 0){
			hwlib::cout << "Gyro z failed\n";
		}
		return false;
	}
}

bool testCalibrate(auto & mpu){
	int16_t accelx = mpu.getAccelX() - mpu.getOffsetAccelX(); 
	int16_t accely = mpu.getAccelY() - mpu.getOffsetAccelY();  
	int16_t accelz = mpu.getAccelZ() - mpu.getOffsetAccelZ(); 
	int16_t gyrox = mpu.getGyroX() - mpu.getOffsetGyroX(); 
	int16_t gyroy = mpu.getGyroY() - mpu.getOffsetGyroY();  
	int16_t gyroz = mpu.getGyroZ() - mpu.getOffsetGyroZ();
	bool ax = between(accelx, -100, 100);
	bool ay = between(accely, -100, 100);
	bool az = between(accelz, -100, 100);
	bool gx = between(gyrox, -100, 100);
	bool gy = between(gyroy, -100, 100);
	bool gz = between(gyroz, -100, 100);
	if(ax && ay && az && gx && gy && gz){
		return true;
	} else {
		if(ax == 0){
			hwlib::cout << "Gyro x failed\n";
		}
		if(ay == 0){
			hwlib::cout << "Gyro y failed\n";
		}
		if(az == 0){
			hwlib::cout << "Gyro z failed\n";
		}
		if(gx == 0){
			hwlib::cout << "Gyro x failed\n";
		}
		if(gy == 0){
			hwlib::cout << "Gyro y failed\n";
		}
		if(gz == 0){
			hwlib::cout << "Gyro z failed\n";
		}
		return false;
	}
}

void test(auto & mpu){
	mpu.setAccelGyro();
	mpu.calibrate();
	if(testWhoAmI(mpu) == 0){
		hwlib::cout << "Who am I failed\n";
	}
	if(testAccel(mpu) == 0){
		hwlib::cout << "Accel failed\n";
	}
	if(testGyro(mpu) == 0){
		hwlib::cout << "Gyro failed\n";
	}
	if(testCalibrate(mpu) == 0){
		hwlib::cout << "Calibration failed\n";
	}
	hwlib::cout << "Testing done\n";
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
	
	test(mpu);
	
	oled.clear();
	auto font = hwlib::font_default_8x8();
	auto display= hwlib::window_ostream( oled, font );
	
	mpu.calibrate();
	for(;;){
		mpu.setAccelGyro();
		mpu.setTemp();
		display << "\f"
		<< "Who? " << mpu.whoAmI() << "\n" 
		<< "Temp: " << mpu.getTempInCelcius() << " Celcuis\n" 
		<< "Accel x: " << mpu.getAccelX() - mpu.getOffsetAccelX() << "\n" 
		<< "Accel y: " << mpu.getAccelY() - mpu.getOffsetAccelY() << "\n"  
		<< "Accel z: " << mpu.getAccelZ() - mpu.getOffsetAccelZ() << "\n" 
		<< "Gyro x: " << mpu.getGyroX() - mpu.getOffsetGyroX()<< "\n" 
		<< "Gyro y: " << mpu.getGyroY() - mpu.getOffsetGyroX()<< "\n"  
		<< "Gyro z: " << mpu.getGyroZ() - mpu.getOffsetGyroX()<< "\n" << hwlib::flush;
		hwlib::wait_ms(1000);
	}
}
