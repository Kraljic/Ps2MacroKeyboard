################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MacroKeyboard/AsciiToHidTranscoder/Src/ascii_to_hid.cpp 

OBJS += \
./MacroKeyboard/AsciiToHidTranscoder/Src/ascii_to_hid.o 

CPP_DEPS += \
./MacroKeyboard/AsciiToHidTranscoder/Src/ascii_to_hid.d 


# Each subdirectory must supply rules for building sources it contributes
MacroKeyboard/AsciiToHidTranscoder/Src/%.o MacroKeyboard/AsciiToHidTranscoder/Src/%.su: ../MacroKeyboard/AsciiToHidTranscoder/Src/%.cpp MacroKeyboard/AsciiToHidTranscoder/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MacroKeyboard-2f-AsciiToHidTranscoder-2f-Src

clean-MacroKeyboard-2f-AsciiToHidTranscoder-2f-Src:
	-$(RM) ./MacroKeyboard/AsciiToHidTranscoder/Src/ascii_to_hid.d ./MacroKeyboard/AsciiToHidTranscoder/Src/ascii_to_hid.o ./MacroKeyboard/AsciiToHidTranscoder/Src/ascii_to_hid.su

.PHONY: clean-MacroKeyboard-2f-AsciiToHidTranscoder-2f-Src

