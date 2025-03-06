/*
 * mpu9250.h
 *
 *  Created on: Mar 2, 2025
 *      Author: sragh
 */

#ifndef SRC_MPU9250_H_
#define SRC_MPU9250_H_

#include <stdint.h>

#define DEVICE_ADDRESS 0x68


#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACCEL 28
#define REG_USR_CTRL 107
#define REG_DATA 59

void mpu9250init();

int16_t mpu9250read();

#endif /* SRC_MPU9250_H_ */
