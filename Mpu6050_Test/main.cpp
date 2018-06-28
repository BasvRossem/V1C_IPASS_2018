#include "hwlib.hpp"
#include "MPU6050.hpp"
#include "MPU6050_Test.hpp"

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
	mpu.setFullScaleAccelRange(2);
	mpu.setFullScaleGyroRange(2);
}
