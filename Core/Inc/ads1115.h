/*
 * ads1115.h
 *
 *  Created on: Aug 27, 2020
 *      Author: thorne
 */

#ifndef INC_ADS1115_H_
#define INC_ADS1115_H_

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include<inttypes.h>


/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
#define ADS1115_ADDRESS (0x48) ///< 1001 000 (ADDR = GND)
/*=========================================================================*/

/*=========================================================================
    CONVERSION DELAY (in mS)
    -----------------------------------------------------------------------*/
#define ADS1115_CONVERSIONDELAY (9) ///< Conversion delay
/*=========================================================================*/

/*=========================================================================
    POINTER REGISTER
    -----------------------------------------------------------------------*/
#define ADS1115_REG_POINTER_MASK (0x03)      ///< Point mask
#define ADS1115_REG_POINTER_CONVERT (0x00)   ///< Conversion
#define ADS1115_REG_POINTER_CONFIG (0x01)    ///< Configuration
#define ADS1115_REG_POINTER_LOWTHRESH (0x02) ///< Low threshold
#define ADS1115_REG_POINTER_HITHRESH (0x03)  ///< High threshold
/*=========================================================================*/

/*=========================================================================
    CONFIG REGISTER
    -----------------------------------------------------------------------*/
#define ADS1115_REG_CONFIG_OS_MASK   	(0x80) ///< OS Mask
#define ADS1115_REG_CONFIG_OS_SINGLE  	(0x01) ///< Write: Set to start a single-conversion
#define ADS1115_REG_CONFIG_OS_BUSY    	(0x00) ///< Read: Bit = 0 when conversion is in progress
#define ADS1115_REG_CONFIG_OS_NOTBUSY 	(0x01) ///< Read: Bit = 1 when device is not performing a conversion

#define ADS1115_REG_CONFIG_MUX_DIFF_0_1 (0x00) ///< Differential P = AIN0, N = AIN1 (default)
#define ADS1115_REG_CONFIG_MUX_DIFF_0_3 (0x01) ///< Differential P = AIN0, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_1_3 (0x02) ///< Differential P = AIN1, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_2_3 (0x03) ///< Differential P = AIN2, N = AIN3
#define ADS1115_REG_CONFIG_MUX_SINGLE_0 (0x04) ///< Single-ended AIN0
#define ADS1115_REG_CONFIG_MUX_SINGLE_1 (0x05) ///< Single-ended AIN1
#define ADS1115_REG_CONFIG_MUX_SINGLE_2 (0x06) ///< Single-ended AIN2
#define ADS1115_REG_CONFIG_MUX_SINGLE_3 (0x07) ///< Single-ended AIN3

#define ADS1115_REG_CONFIG_PGA_6_144V 	(0x00) ///< +/-6.144V range = Gain 2/3
#define ADS1115_REG_CONFIG_PGA_4_096V 	(0x01) ///< +/-4.096V range = Gain 1
#define ADS1115_REG_CONFIG_PGA_2_048V  	(0x02) ///< +/-2.048V range = Gain 2 (default)
#define ADS1115_REG_CONFIG_PGA_1_024V 	(0x03) ///< +/-1.024V range = Gain 4
#define ADS1115_REG_CONFIG_PGA_0_512V 	(0x04) ///< +/-0.512V range = Gain 8
#define ADS1115_REG_CONFIG_PGA_0_256V 	(0x05) ///< +/-0.256V range = Gain 16

#define ADS1115_REG_CONFIG_MODE_CONTIN 	(0x00) ///< Continuous conversion mode
#define ADS1115_REG_CONFIG_MODE_SINGLE 	(0x01) ///< Power-down single-shot mode (default)

#define ADS1115_REG_CONFIG_DR_08SPS 	(0x00) ///< 08 samples per second
#define ADS1115_REG_CONFIG_DR_16SPS 	(0x01) ///< 16 samples per second
#define ADS1115_REG_CONFIG_DR_32SPS 	(0x02) ///< 32 samples per second
#define ADS1115_REG_CONFIG_DR_64SPS 	(0x03) ///< 64 samples per second
#define ADS1115_REG_CONFIG_DR_128SPS 	(0x04) ///< 128 samples per second
#define ADS1115_REG_CONFIG_DR_250SPS 	(0x05) ///< 250 samples per second
#define ADS1115_REG_CONFIG_DR_475SPS 	(0x06) ///< 475 samples per second
#define ADS1115_REG_CONFIG_DR_860SPS 	(0x07) ///< 860 samples per second

#define ADS1115_REG_CONFIG_CMODE_TRAD 	(0x00) ///< Traditional comparator with hysteresis (default)
#define ADS1115_REG_CONFIG_CMODE_WINDOW (0x01) ///< Window comparator

#define ADS1115_REG_CONFIG_CPOL_ACTVLOW (0x00) ///< ALERT/RDY pin is low when active (default)
#define ADS1115_REG_CONFIG_CPOL_ACTVHI  (0x01) ///< ALERT/RDY pin is high when active

#define ADS1115_REG_CONFIG_CLAT_NONLAT  (0x00) ///< Non-latching comparator (default)
#define ADS1115_REG_CONFIG_CLAT_LATCH 	(0x01) ///< Latching comparator

#define ADS1115_REG_CONFIG_CQUE_1CONV   (0x00) ///< Assert ALERT/RDY after one conversions
#define ADS1115_REG_CONFIG_CQUE_2CONV   (0x01) ///< Assert ALERT/RDY after two conversions
#define ADS1115_REG_CONFIG_CQUE_4CONV   (0x02) ///< Assert ALERT/RDY after four conversions
#define ADS1115_REG_CONFIG_CQUE_NONE    (0x03) ///< Disable the comparator and put ALERT/RDY in high state (default)
/*=========================================================================*/

//Gyro configuration
struct adsConfig {
	uint8_t OS_MODE;
	uint8_t MUX_MODE;
	uint8_t GAIN_MODE;
	uint8_t OP_MODE;
	uint8_t RATE_MODE;
	uint8_t COMP_MODE;
};

/** OS settings */
enum {
  BEGIN = ADS1115_REG_CONFIG_OS_SINGLE,
};

/** MUX settings */
enum {
  AN0 = ADS1115_REG_CONFIG_MUX_SINGLE_0,
  AN1 = ADS1115_REG_CONFIG_MUX_SINGLE_1,
  AN2 = ADS1115_REG_CONFIG_MUX_SINGLE_2,
  AN3 = ADS1115_REG_CONFIG_MUX_SINGLE_3,
};


/** Gain settings */
enum {
	PGA3 = ADS1115_REG_CONFIG_PGA_2_048V,
	PGA4 = ADS1115_REG_CONFIG_PGA_1_024V,
};

/** OP settings */
enum {
  CONTMOD = ADS1115_REG_CONFIG_MODE_CONTIN,
  SINGMOD = ADS1115_REG_CONFIG_MODE_SINGLE,
};

/** RATE settings */
enum {

	SPS08 = ADS1115_REG_CONFIG_DR_08SPS,
	SPS16 = ADS1115_REG_CONFIG_DR_16SPS,
	SPS32 = ADS1115_REG_CONFIG_DR_32SPS,
	SPS64 = ADS1115_REG_CONFIG_DR_64SPS,
	SPS128 = ADS1115_REG_CONFIG_DR_128SPS,
	SPS250 = ADS1115_REG_CONFIG_DR_250SPS,
};

/** COMP settings */
enum {

	CONV1 = ADS1115_REG_CONFIG_CQUE_1CONV,
	CONV2 = ADS1115_REG_CONFIG_CQUE_2CONV,
	CONV4 = ADS1115_REG_CONFIG_CQUE_4CONV,
	CONVNONE = ADS1115_REG_CONFIG_CQUE_NONE,
};



class ads1115 {
public:
	// Configure ADS1115 function
	void ads1115_config(uint8_t channel, adsConfig& config);
	// Get data from ADS1115
	uint16_t ads1115_data(uint8_t channel, adsConfig& config);

private:
	uint8_t address;
	uint8_t address2;
	uint8_t address3;
};




#endif /* INC_ADS1115_H_ */
