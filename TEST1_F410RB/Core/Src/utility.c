/*
 * utility.c
 *
 *  Created on: Dec 4, 2023
 *      Author: sunil
 */

#include "utility.h"

bool Process_Received_Command_From_Uart(char Command_Buffer[20]) {
	if (Command_Buffer[0] == 'C') {
		// Check if the second character is a digit between 0 and 5
		if (isdigit((unsigned char )Command_Buffer[1])
				&& Command_Buffer[1] >= '0' && Command_Buffer[1] <= '5') {
			Print_UART(
					(const uint8_t*) "VALID COMMAND RECEIVED.. Processing..\0");
		} else {
			Print_UART(
					(const uint8_t*) "Command Failed: Second character is not a digit between 0 and 5 \0\n");
		}
	} else {
		Print_UART(
				(const uint8_t*) "Command Failed: First character is not 'C'\0\n");

	}
	uint64_t hexValue;

	// Copy from the 2nd position to the end
	char hexString[20]; // Assuming the length can be at most 18 characters (plus null terminator)
	strncpy(hexString, Command_Buffer + 2, sizeof(hexString) - 1);
//	hexString[sizeof(hexString) - 1] = '\0'; // Null-terminate the hexString

	// Convert the hexString to a hexadecimal value
	sscanf(hexString, "%" SCNx64, &hexValue);

	return 0;
}
void Print_UART(const uint8_t *message) {
	HAL_UART_Transmit(DEBUG_TX_PORT, message, strlen((const char*) message),
			100);
}
