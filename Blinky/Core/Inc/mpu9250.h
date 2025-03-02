/*
 * mpu9250.h
 *
 *  Created on: Mar 1, 2025
 *      Author: sragh
 */

#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

#include <stdint.h>
//Device ID
#define DEVICE_ADDRESS 0x68

//Gyro
#define FS_GYRO_500 8
#define REG_CONFIG_GYRO 27

//Accelerometer
#define FS_AFS_2G 0
#define REG_CONFIG_ACCEL 28
#define REG_DATA 59

//Sleep Settings
#define REG_USR_CTRL 107

//Configures Gyro, Accel and Wakes up MPU from sleep
void mpu9250init();

// Read IMU Data
int16_t mpu9250read();




#endif /* INC_MPU9250_H_ */
