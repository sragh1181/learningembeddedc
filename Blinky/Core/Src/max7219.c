/*
 * max7219.c
 *
 *  Created on: Mar 1, 2025
 *      Author: sragh
 */

#include <main.h>
#include <stdio.h>
#include <stdint.h>
#include <mpu9250.h>

extern SPI_HandleTypeDef hspi2;;

void MAX7219_Write(uint8_t address, uint8_t data) {
    // Pull CS low to start communication
    HAL_GPIO_WritePin(MAX7219_CS_PORT, MAX7219_CS_PIN, GPIO_PIN_RESET);

    // Send address and data
    HAL_SPI_Transmit(&hspi2, &address, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);

    // Pull CS high to end communication
    HAL_GPIO_WritePin(MAX7219_CS_PORT, MAX7219_CS_PIN, GPIO_PIN_SET);
}

void MAX7219_Init(void) {
    MAX7219_Write(0x09, 0x00); // Decode mode: No decode
    MAX7219_Write(0x0A, 0x08); // Intensity: Medium brightness
    MAX7219_Write(0x0B, 0x07); // Scan limit: Display all 8 digits
    MAX7219_Write(0x0C, 0x01); // Shutdown register: Normal operation
    MAX7219_Write(0x0F, 0x00); // Display test: Off
}

void MAX7219_DisplayRow(uint8_t row, uint8_t value) {
    if (row >= 1 && row <= 8) {
        MAX7219_Write(row, value);
    }// Write value to the specified row
}
