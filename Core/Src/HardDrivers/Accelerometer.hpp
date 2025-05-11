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
#include "SystemDefines.h"


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

#define ACCELEROMETER_I2C_FIFO_DATA_OUT_TAG  0x78

#define ACCELEROMETER_I2C_FIFO_SIZE  ( /* 512 */ 10 * 7)


// #define ACCELEROMETER_I2C_CTRL6_C  0x15


/**********************************************************************************/
enum EAccelerometerAccess
{
	AccelerometerAccess_Enable,
	AccelerometerAccess_Disable,
};

enum EAccelerometerRxMode
{
	AccelerometerRxMode_Register,
	AccelerometerRxMode_Fifo,
};

/**********************************************************************************/
//==================================================================================
class TAccelerometer
{
public:
	////// variables //////


	////// constants //////


	////// functions //////
	ESystemResult Init(void);
	ESystemResult StartFifo(void);
	ESystemResult ReadFifo(void);

	uint16_t GetSizeDataFifo(void)
	{
		return(this->sizeDataFifo);
	}
	uint8_t* GetPtrDataFifo(void)
	{
		return(this->bufferDmaFifo);
	}


	float GetData(void);
	void InterruptFifoReady(void);
	void TxComplete(void);
	void RxComplete(void);


protected:
	////// variables //////


	////// constants //////


	////// functions //////

private:
	////// variables //////
	volatile bool flagFifoReady;
	volatile EAccelerometerRxMode rxMode;
	volatile bool flagRx;
	uint8_t bufferWr[2];
	uint8_t bufferRd[2];

	uint8_t bufferDmaFifo[ACCELEROMETER_I2C_FIFO_SIZE];
	uint16_t sizeDataFifo;

	////// constants //////


	////// functions //////
	ESystemResult Reset(void);
	ESystemResult GyroscopeSetPowerDown(void);
	ESystemResult AccelerometerSetPowerDown(void);
	ESystemResult SetODR(void);
	ESystemResult SetFifo(void);
	ESystemResult EnableLowPowerMode(void);
	ESystemResult EnableUltraLowPowerMode(void);
	ESystemResult EnableAccess(EAccelerometerAccess accelerometerAccess);
	ESystemResult WriteRegister(uint8_t addressRegister, uint8_t byteData);
	ESystemResult ReadRegister(uint8_t addressRegister);
	ESystemResult WaitRxComplete(uint16_t timeout);
	ESystemResult StartReadFifo(void);
	ESystemResult GetStatusFifo(void);


};
//=== end class TAccelerometer =====================================================

/**********************************************************************************/
#endif
