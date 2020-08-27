/*
 * ads1115.cpp
 *
 *  Created on: Aug 27, 2020
 *      Author: thorne
 */


#include "ads1115.h"
#include "I2C.h"

I2C i2c;

void ads1115::ads1115_config(uint8_t channel, adsConfig& config){

  uint8_t buf[5];

  buf[0] = config.OS_MODE<<7 | config.MUX_MODE<<4 | config.GAIN_MODE<<1 | config.OP_MODE;;
  buf[1] = config.RATE_MODE << 5 | 0x00 | config.COMP_MODE;

  uint16_t input = buf[0] << 8 | buf[1];

  i2c.I2C_write(ADS1115_ADDRESS, ADS1115_REG_POINTER_CONFIG, input);

  HAL_Delay(ADS1115_CONVERSIONDELAY);

}






uint16_t ads1115::ads1115_data(uint8_t channel, adsConfig& config){

	uint8_t buf[10];

	switch (channel){
		case 1:{
			  config.MUX_MODE = AN0;

			  buf[0] = config.OS_MODE<<7 | config.MUX_MODE<<4 | config.GAIN_MODE<<1 | config.OP_MODE;
			  buf[1] = config.RATE_MODE << 5 | 0x00 | config.COMP_MODE;

			  uint16_t ch1_in = buf[0] << 8 | buf[1];

			  i2c.I2C_write(ADS1115_ADDRESS, ADS1115_REG_POINTER_CONFIG, ch1_in);

			  HAL_Delay(ADS1115_CONVERSIONDELAY);
			break;
		}
		case 2:{
			config.MUX_MODE = AN1;
			  buf[0] = config.OS_MODE<<7 | config.MUX_MODE<<4 | config.GAIN_MODE<<1 | config.OP_MODE;
			  buf[1] = config.RATE_MODE << 5 | 0x00 | config.COMP_MODE;

			  uint16_t ch2_in = buf[0] << 8 | buf[1];

			  i2c.I2C_write(ADS1115_ADDRESS, ADS1115_REG_POINTER_CONFIG, ch2_in);

			  HAL_Delay(ADS1115_CONVERSIONDELAY);
			break;
		}
		case 3:{
			config.MUX_MODE = AN2;
			  buf[0] = config.OS_MODE<<7 | config.MUX_MODE<<4 | config.GAIN_MODE<<1 | config.OP_MODE;
			  buf[1] = config.RATE_MODE << 5 | 0x00 | config.COMP_MODE;

			  uint16_t ch3_in = buf[0] << 8 | buf[1];

			  i2c.I2C_write(ADS1115_ADDRESS, ADS1115_REG_POINTER_CONFIG, ch3_in);

			  HAL_Delay(ADS1115_CONVERSIONDELAY);
			break;
		}
		case 4:{
			config.MUX_MODE = AN3;
			  buf[0] = config.OS_MODE<<7 | config.MUX_MODE<<4 | config.GAIN_MODE<<1 | config.OP_MODE;
			  buf[1] = config.RATE_MODE << 5 | 0x00 | config.COMP_MODE;

			  uint16_t ch4_in = buf[0] << 8 | buf[1];

			  i2c.I2C_write(ADS1115_ADDRESS, ADS1115_REG_POINTER_CONFIG, ch4_in);

			  HAL_Delay(ADS1115_CONVERSIONDELAY);
			break;
		}
		default:
			break;
	}

	uint8_t AdsArr[6];

	// Read the conversion results
	// Shift 12-bit results right 4 bits for the ADS1115
	i2c.I2C_read(ADS1115_ADDRESS, ADS1115_REG_POINTER_CONVERT,AdsArr,2);

	uint16_t output = AdsArr[0] << 8 | AdsArr[1];

	HAL_Delay(ADS1115_CONVERSIONDELAY);

	return output;


}
