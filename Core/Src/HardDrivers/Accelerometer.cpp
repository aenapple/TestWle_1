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
extern "C" uint8_t Init(void)
{
	return(Accelerometer.Init());
}

extern "C" uint8_t GetStatusFifo(void)
{
	return(Accelerometer.GetStatusFifo());
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	Accelerometer.TxComplete();
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	Accelerometer.RxComplete();
}

void HAL_GPIO_EXTI_Callback(uint16_t gpioPin)
{
	Accelerometer.Int2();
}


/**********************************************************************************/
//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::Init()
{
	uint8_t result;


	result = this->Reset();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	result = this->ReadRegister(ACCELEROMETER_I2C_FUNC_CFG_ACCESS);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	result = this->AccelerometerSetPowerDown();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

//	return(ACCELEROMETER_I2C_RESULT_OK);

	result = this->GyroscopeSetPowerDown();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	result = this->EnableLowPowerMode();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	result = this->EnableUltraLowPowerMode();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	result = this->SetODR();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	result = this->SetFifo();
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}






	return(ACCELEROMETER_I2C_RESULT_OK);
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
void TAccelerometer::Int2()
{
//	this->AccelerometerSetPowerDown();
	__NOP();
	__NOP();
}
//=== end Int2 =====================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::Reset()
{
	uint8_t result;

	/*
	 * Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI)
	 * Software Reset
	 * 0000 0101
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL3_C, 0x05);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end SetODR ===================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::SetFifo()
{
	uint8_t result;


	/*
	 * set 384 (0x180) bytes threshold level
	 * 1000 0000
	 */
//	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL1, 0x80);
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL1, 0x1A);  // DEBUG
	if(result > ACCELEROMETER_I2C_RESULT_OK)
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
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	/*
	 * 0000 - Gyro not batched in FIFO (default);
	 * 1011 - 1.6 Hz
	 * 0000 1011
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL3, 0x0B);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	/*
	 * Enables FIFO threshold interrupt on INT2 pin
	 * 0000 1000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_INT2_CTRL, 0x28);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
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
	result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x01);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}




	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end SetFifo ==================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::GyroscopeSetPowerDown()
{
	uint8_t result;


	/*
	 * 0000 - Power-down
	 * 00 - full-scale - 250dps
	 * 0 - full-scale - disable 150dps
	 * binary - 0000 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL2_G, 0x00);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	// DEBUG
	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL2_G);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}
	// DEBUG


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end GyroscopeSetPowerDown ================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::AccelerometerSetPowerDown()
{
	uint8_t result;


	/*
	 * 0000 - Power-down
	 * 00 - full-scale - 2g (default)
	 * 0 - first stage digital filtering selected (default)
	 * binary - 0000 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL1_XL, 0x00);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	// DEBUG
	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL1_XL);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}
	// DEBUG


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end AccelerometerSetPowerDown ================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::SetODR()
{
	uint8_t result;


	/*
	 * 1011 - 1.6 Hz (low power only)
	 * 00 - full-scale - 2g (default)
	 * 0 - first stage digital filtering selected (default)
	 * binary - 1011 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL1_XL, 0xB0);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	// DEBUG
	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL1_XL);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}
	// DEBUG


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end SetODR ===================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::EnableLowPowerMode()
{
	uint8_t result;


	/*
	 * Edge-sensitive trigger mode is selected
	 * high-performance operating mode disabled
	 * binary - 1001 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL6_C, 0x90);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	// DEBUG
	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL6_C);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}
	// DEBUG


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end EnableLowPowerMode =======================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::EnableUltraLowPowerMode()
{
	uint8_t result;


	/*
	 * Ultra-low-power mode enabled
	 * binary - 1000 0000
	 */
	result = this->WriteRegister(ACCELEROMETER_I2C_CTRL5_C, 0x80);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	// DEBUG
	result = this->ReadRegister(ACCELEROMETER_I2C_CTRL5_C);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}
	// DEBUG


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end EnableUltraLowPowerMode ==================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::EnableAccess(EAccelerometerAccess accelerometerAccess)
{
	uint8_t result;


	if(accelerometerAccess == AccelerometerAccess_Enable)
	{
		result = this->WriteRegister(ACCELEROMETER_I2C_FUNC_CFG_ACCESS, 0x40);
	}
	else
	{
		result = this->WriteRegister(ACCELEROMETER_I2C_FUNC_CFG_ACCESS, 0x00);
	}

	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end EnableAccess =============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::GetStatusFifo()
{
	uint8_t result;


	result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS2);
	if(result > ACCELEROMETER_I2C_RESULT_OK)
	{
		return(result);
	}

	if(this->bufferRd[0] & 0x80)
	{
		result = this->ReadRegister(ACCELEROMETER_I2C_FIFO_STATUS1);
		if(result > ACCELEROMETER_I2C_RESULT_OK)
		{
			return(result);
		}

		////// Reset FIFO mode //////
		result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x00);
		if(result > ACCELEROMETER_I2C_RESULT_OK)
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
		result = this->WriteRegister(ACCELEROMETER_I2C_FIFO_CTRL4, 0x01);
		if(result > ACCELEROMETER_I2C_RESULT_OK)
		{
			return(result);
		}
	}


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end GetStatusFifo ============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::ReadRegister(uint8_t addressRegister)
{
	this->flagRx = false;
	this->bufferWr[0] = addressRegister;
	if(HAL_I2C_Master_Seq_Transmit_IT(&hi2c2, ACCELEROMETER_I2C_DEV_ADDRESS, this->bufferWr, 1, I2C_FIRST_FRAME) != HAL_OK)
	{
		return(ACCELEROMETER_I2C_RESULT_OK + 1);
	}

	while(true)
	{
		if(this->flagRx)
		{
			break;
		}
	}


	return(ACCELEROMETER_I2C_RESULT_OK);
}
//=== end ReadRegister =============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
uint8_t TAccelerometer::WriteRegister(uint8_t addressRegister, uint8_t byteData)
{
	this->bufferWr[0] = addressRegister;
	this->bufferWr[1] = byteData;
	if(HAL_I2C_Master_Transmit(&hi2c2, ACCELEROMETER_I2C_DEV_ADDRESS, this->bufferWr, 2, 100) != HAL_OK)
	{
		return(ACCELEROMETER_I2C_RESULT_OK + 1);  // Error
	}


	return(ACCELEROMETER_I2C_RESULT_OK);
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
	HAL_I2C_Master_Seq_Receive_IT(&hi2c2, ACCELEROMETER_I2C_DEV_ADDRESS, this->bufferRd, 1, I2C_LAST_FRAME);
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
