################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.c \
C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.c \
C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.o \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.d \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.o: C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.c common/Thirdparty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/include" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/Config" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/OS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o: C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S common/Thirdparty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/Config" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.o: C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.c common/Thirdparty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/include" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/Config" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/OS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.o: C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.c common/Thirdparty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/include" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/Config" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/OS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-Thirdparty-2f-SEGGER-2f-SEGGER

clean-common-2f-Thirdparty-2f-SEGGER-2f-SEGGER:
	-$(RM) ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.cyclo ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.d ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.o ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT.su ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.cyclo ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.d ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.o ./common/Thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.su ./common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.cyclo ./common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./common/Thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-common-2f-Thirdparty-2f-SEGGER-2f-SEGGER

