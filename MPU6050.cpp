#include "MPU6050.hpp"

int MPU6050::whoAmI(){
	uint8_t data[1] = {MPU6050_WHO_AM_I};
	i2c_bus.write(deviceAddress, data, 1);
	i2c_bus.read(deviceAddress, data, 1);
	int whoHeIs = data[0];
	return whoHeIs;
}

void MPU6050::wakeUp(){
	byte data[arraySize8] = {MPU6050_PWR_MGMT_1, 0};
	i2c_bus.write(deviceAddress, data, 2);
}

byte MPU6050::read8bit(const byte & address){
	byte data[] = {address};
	i2c_bus.write(deviceAddress, data, sizeof(data) / sizeof(byte));
	i2c_bus.read(deviceAddress, data, sizeof(data) / sizeof(byte));
	return *data;
}

int16_t MPU6050::read16bit(const byte & addressHigh, const byte & addressLow){
	byte dataHigh = read8bit(addressHigh);
	byte dataLow = read8bit(addressLow);
	int16_t conversion = (dataHigh << 8) + dataLow;
	return conversion;
}



void MPU6050::setAccelGyro(){
	setAccel();
	setGyro();
}
void MPU6050::setAccel(){
	setAccelX();
	setAccelY(); 
	setAccelZ();
}
void MPU6050::setAccelX(){
	accelX = read16bit(MPU6050_ACCEL_XOUT_H, MPU6050_ACCEL_XOUT_L);
}
void MPU6050::setAccelY(){
	accelY = read16bit(MPU6050_ACCEL_YOUT_H, MPU6050_ACCEL_YOUT_L);
}
void MPU6050::setAccelZ(){
	accelZ = read16bit(MPU6050_ACCEL_ZOUT_H, MPU6050_ACCEL_ZOUT_L);
}
int16_t MPU6050::getAccelX(){
	return accelX;
}
int16_t MPU6050::getAccelY(){
	return accelY;
}
int16_t MPU6050::getAccelZ(){
	return accelZ;
}

void MPU6050::setGyro(){
	setGyroX();
	setGyroY();
	setGyroZ();
}
void MPU6050::setGyroX(){
	gyroX = read16bit(MPU6050_GYRO_XOUT_H, MPU6050_GYRO_XOUT_L);
}
void MPU6050::setGyroY(){
	gyroY = read16bit(MPU6050_GYRO_YOUT_H, MPU6050_GYRO_YOUT_L);
}
void MPU6050::setGyroZ(){
	gyroZ = read16bit(MPU6050_GYRO_ZOUT_H, MPU6050_GYRO_ZOUT_L);
}
int16_t MPU6050::getGyroX(){
	return gyroX;
}
int16_t MPU6050::getGyroY(){
	return gyroY;
}
int16_t MPU6050::getGyroZ(){
	return gyroZ;
}

void MPU6050::calibrate(){
	hwlib::cout << "Calibration started, keep device still.\n";
	hwlib::wait_ms(250);
	uint32_t deltaAccelX = 0, deltaAccelY = 0, deltaAccelZ = 0;
	uint32_t deltaGyroX = 0, deltaGyroY = 0, deltaGyroZ = 0;
	for(unsigned int i = 0; i < 50; i++){
		setAccelGyro();
		deltaAccelX += getAccelX();
		deltaAccelY += getAccelY();
		deltaAccelZ += getAccelZ();
		
		deltaGyroX += getGyroX();
		deltaGyroY += getGyroY();
		deltaGyroZ += getGyroZ();
		hwlib::wait_ms(50);
	}
	offsetAccelX = deltaAccelX / 50;
	offsetAccelY = deltaAccelY / 50; 
	offsetAccelZ = deltaAccelZ / 50;
	offsetGyroX = deltaGyroX / 50; 
	offsetGyroY = deltaGyroY / 50; 
	offsetGyroZ = deltaGyroZ / 50;
	hwlib::cout << "Calibration complete.\n";
}

uint16_t MPU6050::getOffsetAccelX(){
	return offsetAccelX;
}
uint16_t MPU6050::getOffsetAccelY(){
	return offsetAccelY;
}
uint16_t MPU6050::getOffsetAccelZ(){
	return offsetAccelZ;
}

uint16_t MPU6050::getOffsetGyroX(){
	return offsetGyroX;
}
uint16_t MPU6050::getOffsetGyroY(){
	return offsetGyroY;
}
uint16_t MPU6050::getOffsetGyroZ(){
	return offsetGyroZ;
}