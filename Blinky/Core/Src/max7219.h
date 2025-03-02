/*
 * max7219.h
 *
 *  Created on: Mar 1, 2025
 *      Author: sragh
 */

#ifndef SRC_MAX7219_H_
#define SRC_MAX7219_H_

#define MAX7219_CS_PIN GPIO_PIN_4
#define MAX7219_CS_PORT GPIOA

#include <stdint.h>

void max7219write();
void max7219init();
void MAX7219_DisplayRow(uint8_t row, uint8_t value);


#endif /* SRC_MAX7219_H_ */
