#ifndef FLASH_ACCESS_H
#define FLASH_ACCESS_H

#include <inttypes.h>
#include "flash_address.h"
#include "stm32f1xx_hal.h"

#define CYCLE_BYTE_NUM 4

void Flash_WriteData(uint32_t addr, uint8_t *data, uint16_t Size);

uint8_t Flash_ReadData(uint32_t addr, uint8_t *data, uint16_t Size);

#endif
