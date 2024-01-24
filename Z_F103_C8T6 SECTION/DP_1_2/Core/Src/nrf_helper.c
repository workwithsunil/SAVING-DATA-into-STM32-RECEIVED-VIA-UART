/*
 * nrf_helper.c
 *
 *  Created on: Aug 8, 2023
 *      Author: sunil
 */
#ifndef NRF_HELPER_H
#define NRF_HELPER_H

#include "nrf_helper.h"
#include "stdbool.h"

uint64_t My_Pipe_Address = 0X00;
uint8_t My_Channel_Num = 52;

uint64_t target_pipe_addr = 0x11223344aa;
uint8_t target_channel_addr = 52;

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart2;

void nrf_init(void) {
	NRF24_begin(NRF_CE_GPIO_Port, NRF_CSN_Pin, NRF_CE_Pin, hspi1);
	nrf24_DebugUART_Init(huart2);
	NRF24_setChannel(My_Channel_Num);
	NRF24_setPayloadSize(32);
	NRF24_openReadingPipe(1, My_Pipe_Address);
	NRF24_startListening();
	printRadioSettings();
}
void Switch_to_Transmitt_mode() {
	NRF24_stopListening();
	NRF24_openWritingPipe(target_pipe_addr);
	NRF24_setChannel(target_channel_addr);
}
void Switch_to_Receiver_mode(void) {
	NRF24_stopListening();
	NRF24_setChannel(My_Channel_Num);
	NRF24_openReadingPipe(1, My_Pipe_Address);
	NRF24_startListening();
}
void TRANSMITT_UPDATE_OVER_NRF(char my_tx_data[]) {
	Switch_to_Transmitt_mode();
	for (int i = 0; i < +10; i++) {
		if (!NRF24_write(my_tx_data, 32)) {
			NRF24_write(my_tx_data, 32);
			HAL_UART_Transmit(&huart2,
					(uint8_t*) "Transmitt_update waiting for ack\n",
					strlen("Transmitt_update waiting for ack\n"), 10);
			HAL_Delay(200);
		} else {
			HAL_UART_Transmit(&huart2,
					(uint8_t*) "Transmitt_update Transmitted successfully\n",
					strlen("Transmitt_update Transmitted successfully\n"), 10);
			HAL_Delay(100);
			break;
		}
	}
	Switch_to_Receiver_mode();
}
bool Data_Available_For_Reading_NRF() {
	return NRF24_available();
}
bool READ_NRF_AVAILABLE_DATA(void *buf, uint8_t len) {
	if (NRF24_read(buf, len)) {
		return true;
	}
	return false;
}
#endif
