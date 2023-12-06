/*
 * utility.c
 *
 *  Created on: Dec 4, 2023
 *      Author: sunil
 */

#include "utility.h"

bool Process_Received_Command_From_Uart(char Command_Buffer_1[]) {
	if (Command_Buffer_1[0] == 'C') {
		// Check if the second character is a digit between 0 and 5
		if (isdigit((unsigned char )Command_Buffer_1[1])
				&& Command_Buffer_1[1] >= '0' && Command_Buffer_1[1] <= '5') {
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

	uint64_t hexValue = 0;

	// Copy from the 2nd position to the end
	char hex_64_String[20] = ""; // Assuming the length can be at most 18 characters (plus null terminator)
	strncpy(hex_64_String, Command_Buffer_1 + 2, 20);

	// Convert the hexString to a hexadecimal value
	for (int i = 0; hex_64_String[i] != '\0'; i++) {
		hexValue = hexValue << 4;

		if (hex_64_String[i] >= '0' && hex_64_String[i] <= '9') {
			hexValue += hex_64_String[i] - '0';
		} else if (hex_64_String[i] >= 'A' && hex_64_String[i] <= 'F') {
			hexValue += hex_64_String[i] - 'A' + 10;
		} else if (hex_64_String[i] >= 'a' && hex_64_String[i] <= 'f') {
			hexValue += hex_64_String[i] - 'a' + 10;
		}
	}
	hexValue++;
	return 0;
}
void Print_UART(const uint8_t *message) {
	HAL_UART_Transmit(DEBUG_TX_PORT, message, strlen((const char*) message),
			100);
}
