#include "../Inc/macro_keyboard.h"
#include "../../Ps2Keyboard/Inc/ps2_key.h"
#include "../../Ps2Keyboard/Inc/ps2_keyboard_reader.h"
#include "../../Ps2ToHidTranscoder/Inc/ps2_to_hid_transcoder.h"
#include "../../Macro/Inc/macro_util.h"
#include "../../Timer/Inc/delay_util.h"
#include "../../HidKeyboard/Inc/hid_key_codes.h"

using namespace ps2_keyboard;
using namespace ps2_to_hid_transcoder;
using namespace macro_api;
using namespace hid_keyboard;
using namespace delay_util;

namespace macro_keyboard {
    MacroKeyboardConfig *MacroKeyboard::macroKeyboardConfig = 0;

    HidKeyboardState *MacroKeyboard::inputKeyboardState = 0;
    MacroExecutor *MacroKeyboard::macroExecutor = 0;
    void (*MacroKeyboard::receivePs2Data)(uint8_t) = 0;

    uint8_t MacroKeyboard::keyNotHandled = 0;

    MacroKeyboard::MacroKeyboard() {}

    void MacroKeyboard::init(MacroKeyboardConfig *macroKeyboardConfig) {
        // Save macro keyboard config
        MacroKeyboard::macroKeyboardConfig = macroKeyboardConfig;

        // Init delay
        Delay::init(macroKeyboardConfig->delayMethod);
        Ps2HidMap::init();

        // Register receive callback
        MacroKeyboard::receivePs2Data = &Ps2KeyboardReader::receivePs2Date;

        // Register Ps2InputKeyboard state
        MacroKeyboard::inputKeyboardState = new HidKeyboardState(255, 0);

        // Create MacroExecutor for executing macros
        static HidKeyboardState *macroOutKeyboardState = new HidKeyboardState(macroKeyboardConfig->reportId,macroKeyboardConfig->sendReportMethod);
        static MacroCommandHandler *macroCommandHandler = new MacroCommandHandler(macroOutKeyboardState);
        MacroKeyboard::macroExecutor = new MacroExecutor(macroKeyboardConfig->macroDataAddress, macroCommandHandler);
    }

    void MacroKeyboard::run() {
        Ps2Key ps2Key;
        HidKey hidKey;
        uint8_t macroExecutinStatus = MacroExecutor::NOT_EXECUTED;

        if (Ps2KeyboardReader::keyAvailable()) {
            // Read key from PS2 keyboard
            ps2Key = Ps2KeyboardReader::getNextKey();
            if (ps2Key.error)
                return;

            // Translate ps2 key to hid key
            hidKey = Ps2ToHidTranscoder::transcode(ps2Key);

            // Check state of the new key, depends for how to handle macro
            if (hidKey.released && keyNotHandled) {
                // Key up event

                // Try to execute macro in active profile
                if (macroKeyboardConfig->activeProfile != HID_PROFILE_DEFAULT) {
                    macroExecutinStatus = _executeMacro(macroKeyboardConfig->activeProfile);
                }

                // Try to execute macro in default profile if it does not exist in active profile
                if (macroExecutinStatus != MacroExecutor::EXECUTED) {
                    macroExecutinStatus = _executeMacro(HID_PROFILE_DEFAULT);
                }

                keyNotHandled = macroExecutinStatus != MacroExecutor::EXECUTED;
            } else if (!hidKey.released) {
                // Key down event, register that we gonna need to handle macro
                keyNotHandled = 1;
            }

            // Register key
            MacroKeyboard::inputKeyboardState->handleKey(hidKey);
        }
    }

    void MacroKeyboard::setActiveProfile(uint8_t profile) {
        if (profile == HID_PROFILE_DEFAULT
            || (profile >= HID_PROFILE_0 && profile <= HID_PROFILE_3)) {
            macroKeyboardConfig->activeProfile = profile;
        }
    }

    uint8_t MacroKeyboard::_executeMacro(uint8_t profile) {
        uint32_t macroTriggerCode;

        // get trigger code from input keyboard and try find macro
        macroTriggerCode = MacroUtil::getMacroTriggerCode(
                MacroKeyboard::inputKeyboardState->getKeyboardReport(),
                profile);

        return MacroKeyboard::macroExecutor->execute(macroTriggerCode);
    }
}
