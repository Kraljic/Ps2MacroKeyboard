#include "../Inc/macro_command_handler.h"

#include "../Inc/macro_keyboard.h"
#include "../../Memory/Inc/memory_reader.h"
#include "../../Timer/Inc/delay_util.h"
#include "../../AsciiToHidTranscoder/Inc/ascii_to_hid.h"
#include "../../AsciiToHidTranscoder/Inc/ascii_to_hid_v2.h"

using namespace memory_access;
using namespace transcoders;
using namespace delay_util;
using namespace hid_keyboard;

namespace macro_api
{
    MacroCommandHandler::MacroCommandHandler(HidKeyboardState *keyboardState)
    {
        this->keyboardState = keyboardState;
    }

    void *MacroCommandHandler::handleCommand(void *data)
    {
        uint8_t cmd = getNextByte(&data);

        if (cmd == CMD_END)
        {
            // End command, return null pointer
            return 0;
        }

        if (cmd & CMD_EXTENDED)
        {
            // Handle extended command
            switch (cmd)
            {
            case CMD_KEY_STREAM:
                keyStream(&data, cmd);
                break;
            case CMD_KEY_STREAM_V2:
                keyStreamV2(&data, cmd);
                break;
            case CMD_SELECT_PROFILE:
                selectProfile(&data, cmd);
                break;
            default:
                return 0;
            }
        }
        else
        {
            // Handle normal command
            uint8_t shortCmd = (cmd & CMD_MASK) >> CMD_COMMAND_OFFSET_BITS;

            switch (shortCmd)
            {
            case CMD_KEY_DOWN:
                keyDown(&data, cmd);
                break;
            case CMD_KEY_UP:
                keyUp(&data, cmd);
                break;
            case CMD_KEY_PRESS:
                keyPress(&data, cmd);
                break;
            case CMD_DELAY_SHORT:
                delayShort(&data, cmd);
                break;
            case CMD_DELAY_LONG:
                delayLong(&data, cmd);
                break;
            case CMD_DELAY_LONG_LONG:
                delayLongLong(&data, cmd);
                break;
            default:
                return 0;
            }
        }

        return data;
    }

    void MacroCommandHandler::keyDown(void **data, uint8_t cmd)
    {
        uint8_t includesModKey = cmd & CMD_MOD_KEY_MASK;
        uint8_t payloadSize = cmd & CMD_PAYLOAD_SIZE_MASK;

        while (payloadSize-- > 0)
        {
            uint8_t hidKey = getNextByte((void **)data);

            this->keyboardState->keyDown(hidKey, includesModKey);
            this->keyboardState->sendReport();

            includesModKey = 0; // Only first key can be mod key
        }

        this->keyboardState->sendReport();
    }

    void MacroCommandHandler::keyUp(void **data, uint8_t cmd)
    {
        uint8_t includesModKey = cmd & CMD_MOD_KEY_MASK;
        uint8_t payloadSize = cmd & CMD_PAYLOAD_SIZE_MASK;

        while (payloadSize-- > 0)
        {
            uint8_t hidKey = getNextByte(data);

            this->keyboardState->keyUp(hidKey, includesModKey);
            this->keyboardState->sendReport();

            includesModKey = 0; // Only first key can be mod key
        }
    }

    void MacroCommandHandler::keyPress(void **data, uint8_t cmd)
    {
        // Create tmp var so we can repeat same command
        void *dataTmp = *data;

        this->keyDown(&dataTmp, cmd);
        this->keyUp(data, cmd);
    }

    void MacroCommandHandler::delayShort(void **data, uint8_t cmd)
    {
        uint8_t ticks = getNextByte(data);
        Delay::delayShort(ticks);
    }

    void MacroCommandHandler::delayLong(void **data, uint8_t cmd)
    {
        uint8_t ticks = getNextByte(data);
        Delay::delayLong(ticks);
    }

    void MacroCommandHandler::delayLongLong(void **data, uint8_t cmd)
    {
        uint32_t ticks = getNextInt(data);
        Delay::delayLongLong(ticks);
    }

    void MacroCommandHandler::keyStream(void **data, uint8_t cmd)
    {
        uint8_t ticks = getNextByte(data);
        uint16_t size = getNextShort(data);

        char c;
        uint16_t hidKeys;
        uint8_t mod;
        uint8_t key;

        // For each key -> press, sleep, release, sleep
        for (int i = 0; i < size; i++)
        {
            c = getNextByte(data);
            hidKeys = AsciiToHidTranscoder::asciiToHid(c);

            if (!hidKeys)
                continue;

            // Decode mode and key
            mod = hidKeys >> 8;
            key = hidKeys & 0xFF;

            // Press mod key (if present) then actual key and send report
            if (mod) {
                this->keyboardState->keyDown(mod, 1);
                this->keyboardState->sendReport();
            }
            this->keyboardState->keyDown(key, 0);
            this->keyboardState->sendReport();

            Delay::delayShort(ticks);

            // Release mod key (if present) then actual key and send report
            if (mod) {
                this->keyboardState->keyUp(mod, 1);
                this->keyboardState->sendReport();
            }
            this->keyboardState->keyUp(key, 0);
            this->keyboardState->sendReport();

            Delay::delayShort(ticks);
        }
    }

    void MacroCommandHandler::keyStreamV2(void **data, uint8_t cmd) {

        uint8_t ticks = getNextByte(data);
        uint16_t size = getNextShort(data);

        char c;
        uint8_t *numpadKeys;
        uint8_t *key;

        // For each key -> press, sleep, release, sleep
        for (int i = 0; i < size; i++)
        {
            c = getNextByte(data);

            numpadKeys = AsciiToHidTranscoderV2::asciiToHid(c);

            if (numpadKeys[0] == HID_KEY_NONE
                || numpadKeys[0] == HID_KEY_MOD_LSHIFT) {
                // Handle alphabet letters and common keys
                if (numpadKeys[0]) {
                    this->keyboardState->keyDown(numpadKeys[0], 1);
                    this->keyboardState->sendReport();
                    Delay::delayShort(ticks);
                }

                this->keyboardState->keyDown(numpadKeys[1], 0);
                this->keyboardState->sendReport();

                Delay::delayShort(ticks);

                this->keyboardState->keyUp(numpadKeys[1], 0);
                this->keyboardState->sendReport();

                if (numpadKeys[0]) {
                    this->keyboardState->keyUp(numpadKeys[0], 1);
                    this->keyboardState->sendReport();
                    Delay::delayShort(ticks);
                }
            } else {
                this->keyboardState->keyDown(numpadKeys[0], 1);
                this->keyboardState->sendReport();

                Delay::delayShort(ticks);

                for (key = numpadKeys + 1; *key != 0 && key < key + 3; key++) {
                    this->keyboardState->keyDown(*key, 0);
                    this->keyboardState->sendReport();

                    Delay::delayShort(ticks);

                    this->keyboardState->keyUp(*key, 0);
                    this->keyboardState->sendReport();

                    Delay::delayShort(ticks);
                }

                this->keyboardState->keyUp(numpadKeys[0], 1);
                this->keyboardState->sendReport();
            }
        }
    }

    void MacroCommandHandler::selectProfile(void **data, uint8_t cmd) {
        uint8_t profile = getNextByte(data);

        macro_keyboard::MacroKeyboard::setActiveProfile(profile);
    }

}