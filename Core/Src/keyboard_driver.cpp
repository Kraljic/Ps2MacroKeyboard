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
#include "../../HidKeyboard/Inc/hid_key_codes.h"

using namespace macro_keyboard;

#define REPORT_ID 1
#define MACRO_DATA_ADR ((void*)FLASH_PAGE(64))
#define REPORT_SIZE (sizeof(keyboard_api::KeyboardReport))

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t ps2ScanCodeBuffer = 0;
uint8_t outBuffer[4][REPORT_SIZE] = {0};
uint8_t outBufferIndex = 0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *husart) {
	MacroKeyboard::receivePs2Data(ps2ScanCodeBuffer);
}

void send_report_to_usb(keyboard_api::KeyboardReport *kr) {
    memcpy(outBuffer[outBufferIndex], kr, REPORT_SIZE);

	USBD_HID_SendReport(&hUsbDeviceFS, outBuffer[outBufferIndex], REPORT_SIZE);

    HAL_Delay(1);
}

void setup() {
    static MacroKeyboardConfig config = { 0 };

	// Setup ps2 receiver
	HAL_UART_Receive_DMA(&huart1, &ps2ScanCodeBuffer, 1);

	// Create macro keyboard config
	config.delayMethod = &HAL_Delay;
	config.sendReportMethod = &send_report_to_usb;
	config.macroDataAddress = MACRO_DATA_ADR;
	config.reportId = REPORT_ID;
    config.activeProfile = HID_PROFILE_DEFAULT;

	// Initialize macro keyboard
	MacroKeyboard::init(&config);

}

void loop() {
	MacroKeyboard::run();
}
