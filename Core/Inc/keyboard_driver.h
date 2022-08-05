/*
 * keyboard_driver.h
 *
 *  Created on: Apr 5, 2021
 *      Author: marko
 */

#ifndef INC_KEYBOARD_DRIVER_H_
#define INC_KEYBOARD_DRIVER_H_

#include <inttypes.h>
#include <usbd_hid.h>
#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void setup();
void loop();

#ifdef __cplusplus
}
#endif

#endif /* INC_KEYBOARD_DRIVER_H_ */
