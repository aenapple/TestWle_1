/**********************************************************************************/
/**
 *  @file Accelerometer.cpp
 *  @brief ...
 *
 *  @copyright (c) 2025 Cattlescan, Inc. All rights reserved. \n
 */
/**********************************************************************************/
#include "Accelerometer.hpp"
#include <string.h>


TAccelerometer Accelerometer;
/**********************************************************************************/
extern I2C_HandleTypeDef hi2c2;


/**********************************************************************************/


/**********************************************************************************/
//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::Init()
{
	ESystemResult result;


	result = this->Reset();
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->ReadRegister(ACCELEROMETER_I2C_FUNC_CFG_ACCESS);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->AccelerometerSetPowerDown();
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->GyroscopeSetPowerDown();
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->EnableLowPowerMode();
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->EnableUltraLowPowerMode();
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->SetODR();
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	result = this->SetFifo();
	if(result != SystemResult_Ok)
	{
		return(result);
	}






	return(SystemResult_Ok);
}
//=== end Init =====================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
float TAccelerometer::GetData()
{
//	HAL_StatusTypeDef halResult;
//	int16_t sTemperature;
//	float fTemperature;
//	uint8_t bufferTemperature[2];


//	ReadRegister(TS_I2C_START_MESURE_ADDRESS);
//
//	HAL_Delay(2);
//
//	ReadRegister(TS_I2C_CONFIG_ADDRESS);
//
//	this->bufferWr[0] = TS_I2C_START_MESURE_ADDRESS;
//	this->bufferWr[1] = (TS_I2C_MESURE_MODE << 6);
//	if(HAL_I2C_Master_Transmit(&hi2c2, TS_I2C_DEV_ADDRESS, this->bufferWr, 2, 100) != HAL_OK)
//	{
//		return(TS_I2C_ERROR_MARKER);
//	}
//
//	HAL_Delay(10);
//
//	ReadRegister(TS_I2C_RESULT_MESURE_ADDRESS0);
//	bufferTemperature[0] = this->bufferRd[0];
//
//	HAL_Delay(2);
//
//	ReadRegister(TS_I2C_RESULT_MESURE_ADDRESS1);
//	bufferTemperature[1] = this->bufferRd[0];
//
//	memcpy((void*)&sTemperature, (void*)bufferTemperature, 2);
//
//	fTemperature = (float)sTemperature / 256 + 25;


	return(1);
}
//=== end GetData ==================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
void TAccelerometer::InterruptFifoReady()
{
//	__NOP();
//	__NOP();

	this->flagFifoReady = true;

}
//=== end InterruptFifoReady =======================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::Reset()
{
	ESystemResult result;

	/*
	 * Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI)
	 * Software Reset
	 * 0000 0101
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL3_C, 0x05);
	if(result != SystemResult_Ok)
	{
		return(result);
	}


	return(SystemResult_Ok);
}
//=== end SetODR ===================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::SetFifo()
{
	ESystemResult result;


	/*
	 * set 384 (0x180) bytes threshold level
	 * 1000 0000
	 */
//	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL1, 0x80);
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL1, 0x0A);  // DEBUG
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	/*
	 * 1 - set 384 (0x180) bytes threshold level
	 * 1- FIFO depth is limited to threshold level
	 * 00 - Non-compressed data writing is not forced
	 * 1000 0001
	 */
//	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL2, 0x81);
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL2, 0x80);  // DEBUG
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	/*
	 * 0000 - Gyro not batched in FIFO (default);
	 * 1011 - 1.6 Hz
	 * 0000 1011
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL3, 0x0B);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	this->flagFifoReady = false;

	/*
	 * Enables FIFO threshold interrupt on INT2 pin
	 * 0000 1000
	 */
//	result = this->WriteRegister(ACCELEROMETER_I2C_INT2_CTRL, 0x08);
//	if(result > ACCELEROMETER_I2C_RESULT_OK)
//	{
//		return(result);
//	}

	/*
	 * Enables FIFO threshold interrupt on INT1 pin
	 * 0000 1000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_INT1_CTRL, 0x08);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	////// Start FIFO mode //////
	/*
	 * 00 - Timestamp not batched in FIFO (default)
	 * 00 - Temperature not batched in FIFO (default)
	 * 001 - FIFO mode: stops collecting data when FIFO is full
	 * 0000 0001
	 */
//	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x01);
//	if(result != SystemResult_Ok)
//	{
//		return(result);
//	}


	return(SystemResult_Ok);
}
//=== end SetFifo ==================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::GyroscopeSetPowerDown()
{
	ESystemResult result;


	/*
	 * 0000 - Power-down
	 * 00 - full-scale - 250dps
	 * 0 - full-scale - disable 150dps
	 * binary - 0000 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL2_G, 0x00);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	// DEBUG
//	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL2_G);
//	if(result != AccelerometerResult_Ok)
//	{
//		return(result);
//	}
	// DEBUG


	return(SystemResult_Ok);
}
//=== end GyroscopeSetPowerDown ================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::AccelerometerSetPowerDown()
{
	ESystemResult result;


	/*
	 * 0000 - Power-down
	 * 00 - full-scale - 2g (default)
	 * 0 - first stage digital filtering selected (default)
	 * binary - 0000 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL1_XL, 0x00);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	// DEBUG
//	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL1_XL);
//	if(result != AccelerometerResult_Ok)
//	{
//		return(result);
//	}
	// DEBUG


	return(SystemResult_Ok);
}
//=== end AccelerometerSetPowerDown ================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::SetODR()
{
	ESystemResult result;


	/*
	 * 1011 - 1.6 Hz (low power only)
	 * 00 - full-scale - 2g (default)
	 * 0 - first stage digital filtering selected (default)
	 * binary - 1011 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL1_XL, 0xB0);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	// DEBUG
//	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL1_XL);
//	if(result != SystemResult_Ok)
//	{
//		return(result);
//	}
	// DEBUG


	return(SystemResult_Ok);
}
//=== end SetODR ===================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::EnableLowPowerMode()
{
	ESystemResult result;


	/*
	 * Data enable off
	 * high-performance operating mode disabled
	 * binary - 0001 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL6_C, 0x90);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	// DEBUG
//	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL6_C);
//	if(result != SystemResult_Ok)
//	{
//		return(result);
//	}
	// DEBUG


	return(SystemResult_Ok);
}
//=== end EnableLowPowerMode =======================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::EnableUltraLowPowerMode()
{
	ESystemResult result;


	/*
	 * Ultra-low-power mode enabled
	 * binary - 1000 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL5_C, 0x80);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	// DEBUG
//	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL5_C);
//	if(result != SystemResult_Ok)
//	{
//		return(result);
//	}
	// DEBUG


	return(SystemResult_Ok);
}
//=== end EnableUltraLowPowerMode ==================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::EnableAccess(EAccelerometerAccess accelerometerAccess)
{
	ESystemResult result;


	if(accelerometerAccess == AccelerometerAccess_Enable)
	{
		result = this->WriteRegister(ACCELEROMETER_I2C_FUNC_CFG_ACCESS, 0x40);
	}
	else
	{
		result = this->WriteRegister(ACCELEROMETER_I2C_FUNC_CFG_ACCESS, 0x00);
	}

	if(result != SystemResult_Ok)
	{
		return(result);
	}


	return(SystemResult_Ok);
}
//=== end EnableAccess =============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::GetStatusFifo()
{
	ESystemResult result;


//	result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS2);
//	if(result > ACCELEROMETER_I2C_RESULT_OK)
//	{
//		return(result);
//	}


//	if(this->bufferRd[0] & 0x80)
//	{
		result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS2);
		if(result != SystemResult_Ok)
		{
			return(result);
		}

		this->sizeDataFifo = this->bufferRd[0] & 0x03;
		this->sizeDataFifo <<= 8;

		result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS1);
		if(result != SystemResult_Ok)
		{
			return(result);
		}

		this->sizeDataFifo += this->bufferRd[0];

		////// Reset FIFO mode //////
		result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x00);
		if(result != SystemResult_Ok)
		{
			return(result);
		}

		this->flagFifoReady = false;


//	}


	return(SystemResult_Ok);
}
//=== end GetStatusFifo ============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::ReadFifo()
{
	ESystemResult result;


	result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS2);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	this->sizeDataFifo = this->bufferRd[0] & 0x03;
	this->sizeDataFifo <<= 8;

	result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS1);
	if(result != SystemResult_Ok)
	{
		return(result);
	}

	this->sizeDataFifo += this->bufferRd[0];
	this->sizeDataFifo = this->sizeDataFifo * 7;

//	for(uint16_t i = 0; i < this->sizeDataFifo; i++)
//	{
		result = this->StartReadFifo();
		if(result != SystemResult_Ok)
		{
			return(result);
		}

		result = this->WaitRxComplete(200);
		if(result != SystemResult_Ok)
		{
			return(result);
		}

//	}

	////// Reset FIFO mode //////
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x00);
	if(result != SystemResult_Ok)
	{
		return(result);
	}


	return(SystemResult_Ok);
}
//=== end ReadFifo =================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::StartFifo()
{
	ESystemResult result;


	////// Start FIFO mode //////
	/*
	 * 00 - Timestamp not batched in FIFO (default)
	 * 00 - Temperature not batched in FIFO (default)
	 * 001 - FIFO mode: stops collecting data when FIFO is full
	 * 0000 0001
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x01);
	if(result != SystemResult_Ok)
	{
		return(result);
	}


	return(SystemResult_Ok);
}
//=== end StartFifo ================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::ReadRegister(uint8_t addressRegister)
{
	ESystemResult result;


	this->flagRx = false;
	this->rxMode = AccelerometerRxMode_Register;

	this->bufferWr[0] = addressRegister;
	if(HAL_I2C_Master_Seq_Transmit_IT(&hi2c2, ACCELEROMETER_I2C_DEV_ADDRESS, this->bufferWr, 1, I2C_FIRST_FRAME) != HAL_OK)
	{
		return(SystemResult_ErrorTxI2c2);
	}

	result = this->WaitRxComplete(100);
	if(result != SystemResult_Ok)
	{
		return(result);
	}


	return(SystemResult_Ok);
}
//=== end ReadRegister =============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::WaitRxComplete(uint16_t timeout)
{
	uint32_t startTick;
	uint32_t currentTick;


	startTick = HAL_GetTick();

	while(true)
	{
		if(this->flagRx)
		{
			break;
		}

		currentTick = HAL_GetTick();
		if((currentTick - startTick) > timeout)
		{
			return(SystemResult_Timeout);
		}
	}


	return(SystemResult_Ok);
}
//=== end WaitRxComplete ===========================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::StartReadFifo()
{
	this->flagRx = false;
	this->rxMode = AccelerometerRxMode_Fifo;

	this->bufferWr[0] = ACCELEROMETER_I2C_FIFO_DATA_OUT_TAG;
	if(HAL_I2C_Master_Seq_Transmit_IT(&hi2c2, ACCELEROMETER_I2C_DEV_ADDRESS, this->bufferWr, 1, I2C_FIRST_FRAME) != HAL_OK)
	{
		return(SystemResult_ErrorTxI2c2);
	}

	return(SystemResult_Ok);
}
//=== end StartReadFifo ============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
ESystemResult TAccelerometer::WriteRegister(uint8_t addressRegister, uint8_t byteData)
{
	this->bufferWr[0] = addressRegister;
	this->bufferWr[1] = byteData;
	if(HAL_I2C_Master_Transmit(&hi2c2, ACCELEROMETER_I2C_DEV_ADDRESS, this->bufferWr, 2, 100) != HAL_OK)
	{
		return(SystemResult_ErrorTxI2c2);
	}


	return(SystemResult_Ok);
}
//=== end WriteRegister ============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
void TAccelerometer::TxComplete()
{
	if(this->rxMode == AccelerometerRxMode_Register)
	{
		HAL_I2C_Master_Seq_Receive_IT(&hi2c2,
				ACCELEROMETER_I2C_DEV_ADDRESS,
				this->bufferRd,
				1,
				I2C_LAST_FRAME);
	}
	else
	{
		HAL_I2C_Master_Seq_Receive_IT(&hi2c2,
				ACCELEROMETER_I2C_DEV_ADDRESS,
				this->bufferDmaFifo,
				this->sizeDataFifo,
				I2C_LAST_FRAME);
	}
}
//=== end TxComplete ===============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
void TAccelerometer::RxComplete()
{
	this->flagRx = true;
}
//=== end RxComplete ===============================================================

/**********************************************************************************/
