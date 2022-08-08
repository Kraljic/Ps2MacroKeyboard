#include "../Inc/ascii_to_hid_v2.h"

namespace transcoders
{
    uint8_t AsciiToHidTranscoderV2::hidKeypadLookupMap[] = {
        HID_KEY_KP0,
        HID_KEY_KP1,
        HID_KEY_KP2,
        HID_KEY_KP3,
        HID_KEY_KP4,
        HID_KEY_KP5,
        HID_KEY_KP6,
        HID_KEY_KP7,
        HID_KEY_KP8,
        HID_KEY_KP9,
    };

    uint8_t* AsciiToHidTranscoderV2::asciiToHid(char c)
    {
        static uint8_t buffer[4] = { 0 };

        buffer[0] = 0;
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;

        if ((c >= 'A') && (c <= 'X'))
        {
            c = tolower(c);
            buffer[0] = HID_KEY_MOD_LSHIFT;
            buffer[1] = (c - 'a') + HID_KEY_A;
            return buffer;
        } else if ((c >= 'a') && (c <= 'x'))
        {
            buffer[1] = (c - 'a') + HID_KEY_A;
            return buffer;
        } else if ((c >= '1') && (c <= '9'))
        {
            buffer[1] = (c - '1') + HID_KEY_1;
            return buffer;
        }

        switch (c)
        {
            case '0':
                buffer[1] = HID_KEY_0;
            case '\n':
                buffer[1] = (HID_KEY_ENTER); //enter
                return buffer;
            case '\b':
                buffer[1] =  (HID_KEY_BACKSPACE); //backspace
                return buffer;
            case '\t':
                buffer[1] =  (HID_KEY_TAB); //tab
                return buffer;
            case ' ':
                buffer[1] =  (HID_KEY_SPACE); //space
                return buffer;
            default:
                buffer[0] = HID_KEY_MOD_LALT;
                if (c >= 100) {
                    buffer[1] = hidKeypadLookupMap[c / 100];
                    buffer[2] = hidKeypadLookupMap[c / 10 % 10];
                    buffer[3] = hidKeypadLookupMap[c % 10];
                } else if (c >= 10) {
                    buffer[1] = hidKeypadLookupMap[c / 10];
                    buffer[2] = hidKeypadLookupMap[c % 10];
                } else {
                    buffer[1] = hidKeypadLookupMap[c];
                }
        }



        return buffer;
    }
}