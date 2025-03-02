/*
 * mpu9250.c
 *
 *  Created on: Mar 1, 2025
 *      Author: sragh
 */

#include <mpu9250.h>
#include <main.h>
#include <stdio.h>
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;

uint8_t fs_sel = FS_GYRO_500;
uint8_t accel_config = FS_AFS_2G;


  //this is to set register 27 to binary for full scale gyro
  /* USER CODE BEGIN 2 */
  // TypeDef enum paired with a variable name
  // the left shift by one byte is refereded for r/w bit, adding 0 is the write operation
  // adding one would be read operation
  //
void mpu9250init()
{

	  HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (DEVICE_ADDRESS <<1) + 0, 1, 100);

	  if (ret == HAL_OK)
	  {
		  printf(" Device is connected\n");
	  }
	  else
	  {
		  printf("wires are crossed prolly \n");
	  }

	  //HAL_I2C_Mem_Write(&hi2c1, (0b1101000 << 1), 0x6B, 8, &data, 1, HAL_MAX_DELAY);
	  ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) + 0, REG_CONFIG_GYRO, 1, &fs_sel, 1, 100);

	  if (ret == HAL_OK)
	  {
		  printf("Configuring Gyro\n");
	  }
	  else
	  {
		  printf("Failed to configure gyro");
	  }

	  // Configure the Accelerometer Range
	  ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) + 0, REG_CONFIG_ACCEL, 1, &accel_config, 1, 100);

	  if (ret == HAL_OK)
	  {
		  printf("Configuring Accel\n");
	  }
	  else
	  {
		  printf("Failed to configure accel\n");
	  }


	  //Set up Temperature and Sleep Status
	  uint8_t temp_data = 0;
	  ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) + 0, REG_USR_CTRL, 1, &temp_data, 1, 100);

	  if (ret == HAL_OK)
	  {
		  printf("Exiting from Sleep Mode\n");
	  }
	  else
	  {
		  printf("ZZZZZZZZ");
	  }

}

int16_t mpu9250read()
{
	//+1 because read
	uint8_t data[6]; //2 bytes of data, no need to use & because use of array
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS <<1) + 1, REG_DATA, 1, data, 2, 100);
	int16_t x_acc = ((int16_t)data[0] <<8) | data[1];
	//x_acc = (x_acc/8192)*9.80665;

	return x_acc;


}
