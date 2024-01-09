################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.o: C:/Users/pubud/OneDrive/Desktop/Learning/01\ Firmware/02\ Udemy\ -\ FreeRTOS/workspace/common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.c common/Thirdparty/FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/include" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/Config" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/OS" -I"C:/Users/pubud/OneDrive/Desktop/Learning/01 Firmware/02 Udemy - FreeRTOS/workspace/common/Thirdparty/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-Thirdparty-2f-FreeRTOS-2f-portable-2f-MemMang

clean-common-2f-Thirdparty-2f-FreeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.cyclo ./common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.d ./common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.o ./common/Thirdparty/FreeRTOS/portable/MemMang/heap_4.su

.PHONY: clean-common-2f-Thirdparty-2f-FreeRTOS-2f-portable-2f-MemMang

