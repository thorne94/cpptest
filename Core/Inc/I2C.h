/*
 * I2C.h
 *
 *  Created on: Aug 26, 2020
 *      Author: thorne
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f4xx_hal.h"
#include <cstdint>
#include <cstring>


class I2C{
public:
	//I2C Initialization
	void I2C_Init(I2C_HandleTypeDef *I2Chnd);
	//I2C write function
	void I2C_write(uint8_t devAddr, uint8_t regAddr, uint16_t data);
	//I2C read function
	void I2C_read(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t size);
};


#endif /* INC_I2C_H_ */
