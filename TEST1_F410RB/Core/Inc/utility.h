/*
 * utility.h
 *
 *  Created on: Dec 4, 2023
 *      Author: sunil
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_

#include "stm32f4xx_hal.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "ee.h"

extern UART_HandleTypeDef huart2;
#define DEBUG_TX_PORT &huart2

bool Process_Received_Command_From_Uart(char Command_Buffer[]);
void Print_UART(const uint8_t *message);

#endif /* INC_UTILITY_H_ */
