################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MacroKeyboard/Macro/Src/macro_command_handler.cpp \
../MacroKeyboard/Macro/Src/macro_executor.cpp \
../MacroKeyboard/Macro/Src/macro_finder.cpp \
../MacroKeyboard/Macro/Src/macro_util.cpp 

OBJS += \
./MacroKeyboard/Macro/Src/macro_command_handler.o \
./MacroKeyboard/Macro/Src/macro_executor.o \
./MacroKeyboard/Macro/Src/macro_finder.o \
./MacroKeyboard/Macro/Src/macro_util.o 

CPP_DEPS += \
./MacroKeyboard/Macro/Src/macro_command_handler.d \
./MacroKeyboard/Macro/Src/macro_executor.d \
./MacroKeyboard/Macro/Src/macro_finder.d \
./MacroKeyboard/Macro/Src/macro_util.d 


# Each subdirectory must supply rules for building sources it contributes
MacroKeyboard/Macro/Src/%.o MacroKeyboard/Macro/Src/%.su: ../MacroKeyboard/Macro/Src/%.cpp MacroKeyboard/Macro/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MacroKeyboard-2f-Macro-2f-Src

clean-MacroKeyboard-2f-Macro-2f-Src:
	-$(RM) ./MacroKeyboard/Macro/Src/macro_command_handler.d ./MacroKeyboard/Macro/Src/macro_command_handler.o ./MacroKeyboard/Macro/Src/macro_command_handler.su ./MacroKeyboard/Macro/Src/macro_executor.d ./MacroKeyboard/Macro/Src/macro_executor.o ./MacroKeyboard/Macro/Src/macro_executor.su ./MacroKeyboard/Macro/Src/macro_finder.d ./MacroKeyboard/Macro/Src/macro_finder.o ./MacroKeyboard/Macro/Src/macro_finder.su ./MacroKeyboard/Macro/Src/macro_util.d ./MacroKeyboard/Macro/Src/macro_util.o ./MacroKeyboard/Macro/Src/macro_util.su

.PHONY: clean-MacroKeyboard-2f-Macro-2f-Src

