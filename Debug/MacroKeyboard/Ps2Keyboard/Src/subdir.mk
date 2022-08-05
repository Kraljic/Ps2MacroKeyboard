################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MacroKeyboard/Ps2Keyboard/Src/ps2_keyboard_reader.cpp 

OBJS += \
./MacroKeyboard/Ps2Keyboard/Src/ps2_keyboard_reader.o 

CPP_DEPS += \
./MacroKeyboard/Ps2Keyboard/Src/ps2_keyboard_reader.d 


# Each subdirectory must supply rules for building sources it contributes
MacroKeyboard/Ps2Keyboard/Src/%.o MacroKeyboard/Ps2Keyboard/Src/%.su: ../MacroKeyboard/Ps2Keyboard/Src/%.cpp MacroKeyboard/Ps2Keyboard/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MacroKeyboard-2f-Ps2Keyboard-2f-Src

clean-MacroKeyboard-2f-Ps2Keyboard-2f-Src:
	-$(RM) ./MacroKeyboard/Ps2Keyboard/Src/ps2_keyboard_reader.d ./MacroKeyboard/Ps2Keyboard/Src/ps2_keyboard_reader.o ./MacroKeyboard/Ps2Keyboard/Src/ps2_keyboard_reader.su

.PHONY: clean-MacroKeyboard-2f-Ps2Keyboard-2f-Src

