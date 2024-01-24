/*
 * ADP8XX_DP_SENSOR.h
 *
 *  Created on: Oct 7, 2023
 *      Author: sunil
 */

#ifndef INC_ADP8XX_DP_SENSOR_H_
#define INC_ADP8XX_DP_SENSOR_H_

#include "stm32f1xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
#define DP_SENS_handletype_def hi2c1

HAL_StatusTypeDef dp_sens_init(void);
uint32_t READ_PRESSURE(void);
uint32_t READ_TEMPERATURE(void);

#endif /* INC_ADP8XX_DP_SENSOR_H_ */
