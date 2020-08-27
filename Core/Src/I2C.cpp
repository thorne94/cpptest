/*
 * I2C.cpp
 *
 *  Created on: Aug 27, 2020
 *      Author: thorne
 */


#include "I2C.h"

static I2C_HandleTypeDef i2cHandler;

void I2C::I2C_Init(I2C_HandleTypeDef *I2Chnd){
	//Copy I2C CubeMX handle to local library
	std::memcpy(&i2cHandler, I2Chnd, sizeof(*I2Chnd));
}

/**************************************************************************/
/*!
    @brief  Writes 16-bits to the specified destination register

    @param devAddr I2C address of device
    @param regAddr register address to write to
    @param data value to write to register
*/
/**************************************************************************/
void I2C::I2C_write(uint8_t devAddr, uint8_t regAddr, uint16_t data) {
//Cut input data to register
	uint8_t partA = (uint8_t)((data & 0xFF00) >> 8);
	uint8_t partB = (uint8_t)(data & 0x00FF);
//Put everything into a single buf (register address + data)
	uint8_t buf[3];
	buf[0] = regAddr;
	buf[1] = partA;
	buf[2] = partB;
//Device address
	uint8_t deviceADR = (devAddr<<1);
//Call old HAL to do the dirty work
	HAL_I2C_Master_Transmit(&i2cHandler, deviceADR, buf, 3, 100);
}

/**************************************************************************/
/*!
    @brief  Read 16-bits from the specified destination register

    @param devAddr I2C address of device
    @param regAddr register address to read from
    @param *data pointer to data
    @param size number of bytes being received

    @return 16 bit register value read
*/
/**************************************************************************/
void I2C::I2C_read(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t size) {
	//define buffer
	uint8_t buf[2];
	//shift addr
	uint8_t deviceADR = (devAddr<<1);
	//asign input addr to buffer
	buf[0] = regAddr;
	HAL_I2C_Master_Transmit(&i2cHandler, deviceADR, &buf[0], 1, 10);
	HAL_I2C_Master_Receive(&i2cHandler, deviceADR, data, size, 100);
}

