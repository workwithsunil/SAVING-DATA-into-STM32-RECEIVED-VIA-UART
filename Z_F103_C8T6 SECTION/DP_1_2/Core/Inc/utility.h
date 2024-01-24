/*
 * utility.h
 *
 *  Created on: Jan 6, 2024
 *      Author: sunil
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_

#include "main.h"
#include<stdbool.h>
#include <string.h>
#include <stdint.h>
#include "ee.h"
#include "nRF24L01.h"
#include "nrf_helper.h"
#include "ADP8XX_DP_SENSOR.h"

/*====== DEBUG PORT INITIALIZATION =======*/
#define Debug_Port &huart2
#define PIPE_ADDR_FOR_NRF 0X800F000
extern UART_HandleTypeDef huart2;

void Print_Debug_Data(char *Debug_Msg);
void HANDLE_RECEIVED_MESSAGE_FROM_GATEWAY(void);
void Manage_Received_Data_From_UART(uint8_t UART_DATA[], size_t data_length);

#endif /* INC_UTILITY_H_ */
