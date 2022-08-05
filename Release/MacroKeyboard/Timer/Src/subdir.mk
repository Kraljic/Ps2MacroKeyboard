################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MacroKeyboard/Timer/Src/delay_util.cpp 

OBJS += \
./MacroKeyboard/Timer/Src/delay_util.o 

CPP_DEPS += \
./MacroKeyboard/Timer/Src/delay_util.d 


# Each subdirectory must supply rules for building sources it contributes
MacroKeyboard/Timer/Src/%.o MacroKeyboard/Timer/Src/%.su: ../MacroKeyboard/Timer/Src/%.cpp MacroKeyboard/Timer/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MacroKeyboard-2f-Timer-2f-Src

clean-MacroKeyboard-2f-Timer-2f-Src:
	-$(RM) ./MacroKeyboard/Timer/Src/delay_util.d ./MacroKeyboard/Timer/Src/delay_util.o ./MacroKeyboard/Timer/Src/delay_util.su

.PHONY: clean-MacroKeyboard-2f-Timer-2f-Src

