#include "hwlib.hpp"
#include "MPU6050.hpp"

int main( void ){
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	namespace target = hwlib::target;

	auto sclGyro = target::pin_oc(target::pins::scl);
	auto sdaGyro = target::pin_oc(target::pins::sda);
	auto i2c_bus_Mpu6050 = hwlib::i2c_bus_bit_banged_scl_sda(sclGyro, sdaGyro);
	auto mpu = MPU6050(i2c_bus_Mpu6050); 
	
	mpu.wakeUp();
	
	for(;;){
		mpu.setAccelGyro();
		hwlib::cout << "Accel:" << 
		" X: " << mpu.getAccelX() <<
		" Y: " << mpu.getAccelY() <<
		" Z: " << mpu.getAccelZ() <<
		" Gyro:" <<
		" X: " << mpu.getGyroX() <<
		" Y: " << mpu.getGyroY() <<
		" Z: " << mpu.getGyroZ() << 
		" I am: "<< mpu.whoAmI()<<"\n";
		
	}
}
