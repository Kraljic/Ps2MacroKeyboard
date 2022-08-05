/*
 * keyboard_driver.cpp
 *
 *  Created on: Apr 5, 2021
 *      Author: marko
 */

#include <string.h>
#include "keyboard_driver.h"
#include "../../MacroKeyboard/KeyboardApi/keyboard_report.h"
#include "../../MacroKeyboard/Main/Inc/macro_keyboard.h"
#include "../../MacroKeyboard/Main/Inc/macro_keyboard_config.h"
#include "../../MacroKeyboard/HidKeyboard/Inc/hid_keyboard_state_util.h"
#include "../../Flash/Inc/flash_address.h"

using namespace macro_keyboard;

#define REPORT_ID 1
#define MACRO_DATA_ADR ((void*)FLASH_PAGE(64))

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t ps2ScanCodeBuffer = 0;
char outBuffer[128] = {0};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *husart) {
	MacroKeyboard::receivePs2Data(ps2ScanCodeBuffer);
}

void send_report_to_usb(keyboard_api::KeyboardReport *kr) {
	static keyboard_api::KeyboardReport krStatic = {0};
	krStatic = *kr;

	USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*) &krStatic, 8);

	hid_keyboard::dumpHidKeyboardReport(&krStatic, outBuffer);
	HAL_UART_Transmit_IT(&huart2, (uint8_t *)outBuffer, strlen(outBuffer));
}

void setup() {
	// Setup ps2 receiver
	HAL_UART_Receive_DMA(&huart1, &ps2ScanCodeBuffer, 1);

	// Create macro keyboard config
	MacroKeyboardConfig config = { 0 };
	config.delayMethod = &HAL_Delay;
	config.sendReportMethod = &send_report_to_usb;
	config.macroDataAddress = MACRO_DATA_ADR;
	config.reportId = REPORT_ID;

	// Initialize macro keyboard
	MacroKeyboard::init(&config);

}

void loop() {
	MacroKeyboard::run();
}
