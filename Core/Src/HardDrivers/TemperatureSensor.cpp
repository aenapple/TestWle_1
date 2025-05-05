/**********************************************************************************/
/**
 *  @file TemperatureSensor.cpp
 *  @brief ...
 *
 *  @copyright (c) 2025 Cattlescan, Inc. All rights reserved. \n
 */
/**********************************************************************************/
#include "TemperatureSensor.hpp"
#include <string.h>


TTemperatureSensor TemperatureSensor;
/**********************************************************************************/
extern I2C_HandleTypeDef hi2c2;


/**********************************************************************************/
extern "C" float GetTemperature(void)
{
	return(TemperatureSensor.GetData());
}

//void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//	TemperatureSensor.TxComplete();
//}
//
//void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//	TemperatureSensor.RxComplete();
//}


/**********************************************************************************/
//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
float TTemperatureSensor::GetData()
{
//	HAL_StatusTypeDef halResult;
	int16_t sTemperature;
	float fTemperature;
	uint8_t bufferTemperature[2];


	ReadRegister(TS_I2C_START_MESURE_ADDRESS);

	HAL_Delay(2);

	ReadRegister(TS_I2C_CONFIG_ADDRESS);

	this->bufferWr[0] = TS_I2C_START_MESURE_ADDRESS;
	this->bufferWr[1] = (TS_I2C_MESURE_MODE << 6);
	if(HAL_I2C_Master_Transmit(&hi2c2, TS_I2C_DEV_ADDRESS, this->bufferWr, 2, 100) != HAL_OK)
	{
		return(TS_I2C_ERROR_MARKER);
	}

	HAL_Delay(10);

	ReadRegister(TS_I2C_RESULT_MESURE_ADDRESS0);
	bufferTemperature[0] = this->bufferRd[0];

	HAL_Delay(2);

	ReadRegister(TS_I2C_RESULT_MESURE_ADDRESS1);
	bufferTemperature[1] = this->bufferRd[0];

	memcpy((void*)&sTemperature, (void*)bufferTemperature, 2);

	fTemperature = (float)sTemperature / 256 + 25;


	return(fTemperature);
}
//=== end GetData ==================================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
void TTemperatureSensor::ReadRegister(uint8_t addressRegister)
{
	this->flagTx = false;
	this->bufferWr[0] = addressRegister;
	HAL_I2C_Master_Seq_Transmit_IT(&hi2c2, TS_I2C_DEV_ADDRESS, this->bufferWr, 1, I2C_FIRST_FRAME);

	while(true)
	{
		if(this->flagTx)
		{
			break;
		}
	}

}
//=== end ReadRegister =============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
void TTemperatureSensor::TxComplete()
{
	HAL_I2C_Master_Seq_Receive_IT(&hi2c2, TS_I2C_DEV_ADDRESS, this->bufferRd, 1, I2C_LAST_FRAME);
//	TemperatureSensor.indexRd++;
}
//=== end TxComplete ===============================================================

//==================================================================================
/**
*  Todo: function description.
*
*  @return void .
*/
void TTemperatureSensor::RxComplete()
{
	this->flagTx = true;
}
//=== end RxComplete ===============================================================

/**********************************************************************************/
