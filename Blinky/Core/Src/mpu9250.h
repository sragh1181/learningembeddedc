/*
 * mpu9250.h
 *
 *  Created on: Mar 2, 2025
 *      Author: sragh
 */

#ifndef MPU9250_H_
#define MPU9250_H_

#include <stdint.h>

#define DEVICE_ADDRESS 0x68


#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACCEL 28
#define REG_USR_CTRL 107

#define REG_DATA 67

void mpu9250init(void);

float mpu9250read2(void);

#endif /* MPU9250_H*/
