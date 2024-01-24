/*
 * utility.c
 *
 *  Created on: Jan 6, 2024
 *      Author: sunil
 */

#include "utility.h"

// FUNCTION DEFINITON
uint64_t Get_Pipe_Address(uint8_t nrf_8_t);
void send_DP_sensor_value_to_gateway(void);
char my_node_id[2] = "01";

/*
 @brief print data, and bool is for printing new line after printing the data
 * */
void Print_Debug_Data(char *Debug_Msg) {
	HAL_UART_Transmit(Debug_Port, (uint8_t*) Debug_Msg, strlen(Debug_Msg), 100);
}

/*
 * @brief Here all the data received from the UART WILL BE MANAGED
 * @args will receive the char array and will process it
 * If the command is not starting with * discard it
 * if it starting with * and next array has NRF_ADDR: written, then copy the next two byte and save a
 * corresponding value at the address of NRF data storage
 * */
void Manage_Received_Data_From_UART(uint8_t UART_DATA[], size_t data_length) {
	// Check if the first element is '*'
	if (data_length > 0 && UART_DATA[0] == '*') {
		// Check if the next bytes form the command "NRF_ADDR:"
		if (data_length >= 9
				&& strncmp((char*) &UART_DATA[1], "NRF_ADDR:", 9) == 0) {
			// If the condition is met, copy the next two bytes to another array
			uint8_t nrfAddress[2];
			nrfAddress[0] = UART_DATA[10];
			nrfAddress[1] = UART_DATA[11];
			//process the command
			// Convert ASCII characters to numeric values
			uint8_t highValue = nrfAddress[0] - '0';
			uint8_t lowValue = nrfAddress[1] - '0';
			// Combine the digits into a single uint8_t
			uint8_t nrf_8_t = (highValue * 10) + lowValue;
			//copy the gateway code of finding address, and save the address
			uint64_t NRF_Pipe_Addr = Get_Pipe_Address(nrf_8_t);
			//ERASE THE PAGE BEFORE WRITING
			bool status = ee_format_page(PIPE_ADDR_FOR_NRF, 1);
			if (!status) {
				Print_Debug_Data(
						(char*) "[SETUP STAGE] UNABLE TO ERASE PAGE\n");
			}
			//WRITE IT EEPROM
			if (!ee_write_64(PIPE_ADDR_FOR_NRF, NRF_Pipe_Addr)) {
				Print_Debug_Data(
						(char*) "[UART CB] UNABLE TO WRITE NRF PIPE ADDRES\n");
			} else {
				Print_Debug_Data(
						(char*) "[UART CB] VALID ADDRESS FOUND AND IS SAVED INTO THE EMULATED EEPROM\n");
			}
			//Data written successfully
		} else {
			// Print invalid command if it doesn't match NRF_ADDR:
			Print_Debug_Data((char*) "Invalid command\n");
		}
	} else {
		// Print not a valid command if the first element is not '*'
		Print_Debug_Data((char*) "Not a valid command received from UART\n");
	}
}
uint64_t Get_Pipe_Address(uint8_t nrf_8_t) {
	switch (nrf_8_t) {
	case 1:
		return 0x11223344AA;
	case 2:
		return 0x11223344AB;
	case 3:
		return 0x11223344AC;
	case 4:
		return 0x11223344AD;
	case 5:
		return 0x11223344AE;
	case 6:
		return 0x11223344AF;
	case 7:
		return 0x11223344B0;
	case 8:
		return 0x11223344B1;
	case 9:
		return 0x11223344B2;
	case 10:
		return 0x11223344B3;
	}
	return 0;
}
void HANDLE_RECEIVED_MESSAGE_FROM_GATEWAY(void) {
	char received_data_from_gateway[50] = "";
	HAL_UART_Transmit(&huart2, (uint8_t*) "\n DATA RECEIVED FROM NRF::>> ",
			strlen("\n DATA RECEIVED FROM NRF::>> "), 10);
	NRF24_read(received_data_from_gateway, 5); //store received data
	HAL_UART_Transmit(&huart2, (uint8_t*) received_data_from_gateway, 5, 10);
	char rcvd_node_id[2];
	memcpy(rcvd_node_id, received_data_from_gateway, 2);
	char rcvd_command = received_data_from_gateway[2];

	//============CHECK IF NODE MATCH WITH ID======================//
	if (!(memcmp(rcvd_node_id, my_node_id, 2))) {
		HAL_UART_Transmit(&huart2, (uint8_t*) "\n NODE ID MATCHED",
				strlen("\n NODE ID MATCHED"), 10);
	} else {
		return;
	}
	if (rcvd_command == '0') {
	//Read the command and transmit the DP SENSOR VAL
		//transmit a value
		HAL_UART_Transmit(&huart2, (uint8_t*) "\n TRANSMITTING DP DATA",
				strlen("\n TRANSMITTING DP DATA"), 10);
		send_DP_sensor_value_to_gateway();
	}
}

void send_DP_sensor_value_to_gateway(void) {

	uint32_t PRESSURE = READ_PRESSURE();
//	uint32_t PRESSURE = 90;
	char buffer[20];
	sprintf(buffer, "%u", PRESSURE);

	char my_tx_data[32] = "010";
	my_tx_data[3] = buffer[0];
	my_tx_data[4] = buffer[1];
	my_tx_data[5] = buffer[2];
	my_tx_data[5] = '\r';
	my_tx_data[5] = '\n';
	TRANSMITT_UPDATE_OVER_NRF(my_tx_data); //TRANSMITT MESSAGE TO GATEWAY
}
