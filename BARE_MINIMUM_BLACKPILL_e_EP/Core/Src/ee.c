#include "ee.h"
#include <string.h>

#define   PAGE                  0
#define   SECTOR                1
#define   PAGE_NUM              2

#define _EE_SIZE (1024 * 2) // size of Emulated EEP to be used , here 1KB X TOTAL SIZE OF THE SECTOR OR PAGE U WANNA USE if 1kb X64 means the sector u r using is of 1024
//starting address from where you wanna write data(must be within the sector u r using )
#define  _EE_PAGE_OR_SECTOR    SECTOR
#define _EE_FLASH_BANK FLASH_BANK_1
#define _EE_VOLTAGE_RANGE _EE_VOLTAGE

//##########################################################################################################
bool ee_read(uint32_t Address_To_Read, uint8_t *data, uint32_t len) {
	for (uint32_t i = 0; i < len; i++) {
		*data = (*(__IO uint8_t*) (i + Address_To_Read));
		data++;
	}
	return true;
}

//##########################################################################################################
bool ee_write(uint32_t Address_To_Write, uint8_t *data, uint32_t len) {
	if (data == NULL)
		return false;
	HAL_FLASH_Unlock();
#ifdef FLASH_TYPEPROGRAM_BYTE
	for (uint32_t i = 0; i < len; i++) {
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, i + Address_To_Write,
				(uint64_t) (data[i])) != HAL_OK) {
			HAL_FLASH_Lock();
			return false;
		}
	}
#endif
	return true;
}
//##########################################################################################################
bool ee_format_sector() {
	HAL_FLASH_Unlock();
	uint32_t error;
	FLASH_EraseInitTypeDef flashErase;
#if _EE_PAGE_OR_SECTOR == PAGE
		flashErase.NbPages = 1;
		flashErase.PageAddress = _EE_ADDR_INUSE;
		flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
	#elif _EE_PAGE_OR_SECTOR == SECTOR
	flashErase.NbSectors = 1; //Number of Sector To Be Erased
	flashErase.Sector = _EE_USE_FLASH_PAGE_NUM_OR_SECTOR_NUM;
	flashErase.TypeErase = FLASH_TYPEERASE_SECTORS;
#endif

#ifdef _EE_FLASH_BANK
	flashErase.Banks = _EE_FLASH_BANK;
#endif

#ifdef _EE_VOLTAGE_RANGE
	flashErase.VoltageRange = _EE_VOLTAGE_RANGE;
#endif
	if (HAL_FLASHEx_Erase(&flashErase, &error) == HAL_OK) {
		HAL_FLASH_Lock();
		return true;
	} else {
		return false;
	}
}

