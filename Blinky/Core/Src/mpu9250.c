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


#define LSB_SENSITIVITY 16384.0

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

float mpu9250read2(void) {
    uint8_t data[2];              // Buffer to store raw data
    int16_t raw_x_acc;            // 16-bit signed integer for raw acceleration
    float x_acc_g;                // Acceleration in g

    // Read 2 bytes from X-axis high and low registers
    if (HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1), REG_DATA, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY) != HAL_OK) {
        printf("I2C read error\n");
        return -1.0f;  // Return error value if read fails
    }

    // Combine the high and low bytes into a signed 16-bit value
    raw_x_acc = (int16_t)((data[0] << 8) | data[1]);

    // Print raw data for debugging
    printf("Raw X-axis acceleration: %d\n", raw_x_acc);

    // Convert raw acceleration to g
    x_acc_g = (float)raw_x_acc / LSB_SENSITIVITY;

    // Print converted acceleration for debugging
    printf("Converted X-axis acceleration: %.3f Gs\n", x_acc_g);

    return x_acc_g;
}
