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
	byte dataHigh[] = {MPU6050_ACCEL_XOUT_H};
	byte dataLow[] = {MPU6050_ACCEL_XOUT_L};
	i2c_bus.write(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.write(deviceAddress, dataLow, sizeof(dataLow) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataLow, sizeof(dataLow) / sizeof(byte));
	accelX = (dataHigh[0] << 8) + dataLow[0];
}
void MPU6050::setAccelY(){
	byte dataHigh[] = {MPU6050_ACCEL_YOUT_H};
	byte dataLow[] = {MPU6050_ACCEL_YOUT_L};
	i2c_bus.write(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.write(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	accelY = (dataHigh[0] << 8) + dataLow[0];
}
void MPU6050::setAccelZ(){
	byte dataHigh[] = {MPU6050_ACCEL_ZOUT_H};
	byte dataLow[] = {MPU6050_ACCEL_ZOUT_L};
	i2c_bus.write(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.write(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	accelZ = (dataHigh[0] << 8) + dataLow[0];
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
	byte dataHigh[] = {MPU6050_GYRO_XOUT_H};
	byte dataLow[] = {MPU6050_GYRO_XOUT_L};
	i2c_bus.write(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.write(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	gyroX = (dataHigh[0] << 8) + dataLow[0];
}
void MPU6050::setGyroY(){
	byte dataHigh[] = {MPU6050_GYRO_YOUT_H};
	byte dataLow[] = {MPU6050_GYRO_YOUT_L};
	i2c_bus.write(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.write(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	gyroY = (dataHigh[0] << 8) + dataLow[0];
}
void MPU6050::setGyroZ(){
	byte dataHigh[] = {MPU6050_GYRO_ZOUT_H};
	byte dataLow[] = {MPU6050_GYRO_ZOUT_L};
	i2c_bus.write(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataHigh, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.write(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	i2c_bus.read(deviceAddress, dataLow, sizeof(dataHigh) / sizeof(byte));
	gyroZ = (dataHigh[0] << 8) + dataLow[0];
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
