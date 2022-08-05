#include "../Inc/flash_access.h"

//FLASH write data test
void Flash_WriteData(uint32_t addr, uint8_t *data, uint16_t Size) {
	//1, unlock FLASH
	HAL_FLASH_Unlock();

	//2, erase FLASH
	// Initialize FLASH_EraseInitTypeDef
	FLASH_EraseInitTypeDef f;
	f.TypeErase = FLASH_TYPEERASE_PAGES;
	f.PageAddress = addr;
	f.NbPages = 1;

	// Set PageError
	uint32_t PageError = 0;

	// call the erase function
	HAL_FLASHEx_Erase(&f, &PageError);

	//3, burn to FLASH
	uint64_t TempBuf = 0;
	for (uint32_t i = 0; i < Size; i += CYCLE_BYTE_NUM) {
		TempBuf = 0;
		for (uint8_t j = 0; j < CYCLE_BYTE_NUM && (i + j) < Size; j++) {
			TempBuf |= (*(data + i + j)) << (j * 8);
		}

		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + i, TempBuf);
	}

	//4, lock FLASH
	HAL_FLASH_Lock();
}

// FLASH read data test, successfully returned 1
uint8_t Flash_ReadData(uint32_t addr, uint8_t *data, uint16_t Size) {
	uint64_t temp;
	uint8_t result = 1;

	for (uint32_t i = 0; i < Size; i += CYCLE_BYTE_NUM) {
		temp = *(__IO uint64_t*) (addr + i);
		for (uint8_t j = 0; j < CYCLE_BYTE_NUM && (i + j) < Size; j++) {
			*(data + i + j) = (uint8_t) (temp >> (j * 8)) & 0xFF;
		}
	}

	return result;
}
