/**********************************************************************************/
/**
 *  @file TemperatureSensor.hpp
 *  @brief Header file for TemperatureSensor.cpp
 *
 *  @copyright (c) 2025 Cattlescan, Inc. All rights reserved. \n
 */
/**********************************************************************************/
#ifndef __TemperatureSensor_H
#define __TemperatureSensor_H

/**********************************************************************************/
#include "main.h"


/**********************************************************************************/
#define TS_I2C_DEV_ADDRESS  (0x41 << 1)

#define TS_I2C_RESULT_MESURE_ADDRESS0  0x00  // Register address for reading data 1st byte
#define TS_I2C_RESULT_MESURE_ADDRESS1  0x01  // Register address for reading data 2nd byte

#define TS_I2C_START_MESURE_ADDRESS  0x04  // Register address for measuring
#define TS_I2C_MESURE_MODE           0x03  // Single measurement mode

#define TS_I2C_CONFIG_ADDRESS  0x05         // Register address for configuration
#define TS_I2C_CONFIG_AVG_1    (0x00 << 3)  // 2.2 mSec
#define TS_I2C_CONFIG_AVG_8    (0x01 << 3)  // 5.2 mSec
#define TS_I2C_CONFIG_AVG_16   (0x02 << 3)  // 8.5 mSec
#define TS_I2C_CONFIG_AVG_32   (0x03 << 3)  // 15.3 mSec


#define TS_I2C_ERROR_MARKER  (-130.0f)


/**********************************************************************************/
//==================================================================================
class TTemperatureSensor
{
public:
	////// variables //////


	////// constants //////


	////// functions //////
	float GetData(void);
	void TxComplete(void);
	void RxComplete(void);


protected:
	////// variables //////


	////// constants //////


	////// functions //////

private:
	////// variables //////
	bool flagTx;
	uint8_t bufferWr[2];
	uint8_t bufferRd[2];
//	uint8_t bufferRd[20];
//	uint8_t indexRd;


	////// constants //////
	void ReadRegister(uint8_t addressRegister);


	////// functions //////

};
//=== end class TTemperatureSensor =================================================

/**********************************************************************************/
#endif
