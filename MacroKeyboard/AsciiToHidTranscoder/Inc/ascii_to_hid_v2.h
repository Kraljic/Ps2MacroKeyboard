#ifndef _ASCII_TO_HID_V2_H
#define _ASCII_TO_HID_V2_H

#include <inttypes.h>
#include <ctype.h>
#include "../../HidKeyboard/Inc/hid_key_codes.h"

namespace transcoders {
    class AsciiToHidTranscoderV2 {
    private:
        static uint8_t hidKeypadLookupMap[];

        AsciiToHidTranscoderV2();

    public:
        /** convert ascii character to USB HID Keyboard scancode.
          * it sends keys like ALT+KEYPAD number combination
          * for example 'A' is sent like ALT + (KP_6, KP_5) or in other words ASCII value of 65 = 'A'
          *
          * @returns Array of 3 bytes
          * */

        static uint8_t* asciiToHid(char c);
    };


}

#endif