/**********************************************************************************/
/**
 *  @file Accelerometer.hpp
 *  @brief Header file for Accelerometer.cpp
 *
 *  @copyright (c) 2025 Cattlescan, Inc. All rights reserved. \n
 */
/**********************************************************************************/
#ifndef __Accelerometer_H
#define __Accelerometer_H

/**********************************************************************************/
#include "main.h"


/**********************************************************************************/
#define ACCELEROMETER_I2C_DEV_ADDRESS  0xD6

#define ACCELEROMETER_I2C_FUNC_CFG_ACCESS  0x01

#define ACCELEROMETER_I2C_FIFO_CTRL1  0x07
#define ACCELEROMETER_I2C_FIFO_CTRL2  0x08
#define ACCELEROMETER_I2C_FIFO_CTRL3  0x09
#define ACCELEROMETER_I2C_FIFO_CTRL4  0x0A

#define ACCELEROMETER_I2C_FIFO_STATUS1  0x3A
#define ACCELEROMETER_I2C_FIFO_STATUS2  0x3B

#define ACCELEROMETER_I2C_INT1_CTRL  0x0D
#define ACCELEROMETER_I2C_INT2_CTRL  0x0E

#define ACCELEROMETER_I2C_CTRL1_XL  0x10
#define ACCELEROMETER_I2C_CTRL2_G   0x11

#define ACCELEROMETER_I2C_CTRL3_C  0x12
#define ACCELEROMETER_I2C_CTRL5_C  0x14
#define ACCELEROMETER_I2C_CTRL6_C  0x15




#define ACCELEROMETER_I2C_RESULT_OK  0x00

// #define ACCELEROMETER_I2C_CTRL6_C  0x15


/**********************************************************************************/
enum EAccelerometerAccess
{
	AccelerometerAccess_Enable,
	AccelerometerAccess_Disable,
};


/**********************************************************************************/
//==================================================================================
class TAccelerometer
{
public:
	////// variables //////


	////// constants //////


	////// functions //////
	uint8_t Init(void);
	float GetData(void);
	void Int2(void);
	uint8_t GetStatusFifo(void);
	void TxComplete(void);
	void RxComplete(void);


protected:
	////// variables //////


	////// constants //////


	////// functions //////

private:
	////// variables //////
	bool flagRx;
	uint8_t bufferWr[2];
	uint8_t bufferRd[2];
//	uint8_t bufferRd[20];
//	uint8_t indexRd;


	////// constants //////


	////// functions //////
	uint8_t Reset(void);
	uint8_t SetFifo(void);
	uint8_t GyroscopeSetPowerDown(void);
	uint8_t AccelerometerSetPowerDown(void);
	uint8_t SetODR(void);
	uint8_t EnableLowPowerMode(void);
	uint8_t EnableUltraLowPowerMode(void);
	uint8_t EnableAccess(EAccelerometerAccess accelerometerAccess);
	uint8_t WriteRegister(uint8_t addressRegister, uint8_t byteData);
	uint8_t ReadRegister(uint8_t addressRegister);

};
//=== end class TAccelerometer =====================================================

/**********************************************************************************/
#endif
