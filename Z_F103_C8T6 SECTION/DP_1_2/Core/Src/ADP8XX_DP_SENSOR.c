/*
 * ADP8XX_DP_SENSOR.c
 *
 *  Created on: Oct 7, 2023
 *      Author: sunil
 */

#include "ADP8XX_DP_SENSOR.h"

uint8_t DP_SENSOR_ADDR = 0X25 << 1;
uint32_t i2c_RETRY_TIME = 100;

HAL_StatusTypeDef dp_sens_init(void) {
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_IsDeviceReady(&DP_SENS_handletype_def, DP_SENSOR_ADDR, 2,
			i2c_RETRY_TIME); // is device avaialble ?
	if (ret != HAL_OK) {
		return HAL_ERROR;
	}
	return HAL_OK;
}

uint32_t READ_PRESSURE(void) {
	uint8_t COMMAND[2];
	COMMAND[0] = 0X37;
	COMMAND[1] = 0X2D;
	HAL_I2C_Master_Transmit(&DP_SENS_handletype_def, DP_SENSOR_ADDR, COMMAND, 2,
			100);
	uint8_t DP_data[9] = { 0 };
	HAL_I2C_Master_Receive(&DP_SENS_handletype_def, DP_SENSOR_ADDR, DP_data, 9,
			100);
	int32_t PRESSURE = ((int16_t) DP_data[0] << 8 | DP_data[1]) / 60;
	return PRESSURE;
}
uint32_t READ_TEMPERATURE(void) {
	uint8_t COMMAND[2];
	COMMAND[0] = 0X37;
	COMMAND[1] = 0X2D;
	HAL_I2C_Master_Transmit(&DP_SENS_handletype_def, DP_SENSOR_ADDR, COMMAND, 2,
			100);
	uint8_t DP_data[9] = { 0 };
	HAL_I2C_Master_Receive(&DP_SENS_handletype_def, DP_SENSOR_ADDR, DP_data, 9,
			100);
	int32_t TEMPERATURE = ((int16_t) DP_data[3] << 8 | DP_data[4]) / 200;
	return TEMPERATURE;
}
