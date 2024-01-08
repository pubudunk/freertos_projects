################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include common/Thirdparty/SEGGER/SEGGER/Syscalls/subdir.mk
-include common/Thirdparty/SEGGER/SEGGER/subdir.mk
-include common/Thirdparty/SEGGER/Rec/subdir.mk
-include common/Thirdparty/SEGGER/OS/subdir.mk
-include common/Thirdparty/SEGGER/Config/subdir.mk
-include common/Thirdparty/FreeRTOS/portable/MemMang/subdir.mk
-include common/Thirdparty/FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
-include common/Thirdparty/FreeRTOS/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 006TaskNotifyFromISR
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
006TaskNotifyFromISR.elf \

MAP_FILES += \
006TaskNotifyFromISR.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
006TaskNotifyFromISR.list \


# All Target
all: main-build

# Main-build Target
main-build: 006TaskNotifyFromISR.elf secondary-outputs

# Tool invocations
006TaskNotifyFromISR.elf 006TaskNotifyFromISR.map: $(OBJS) $(USER_OBJS) C:\Users\pubud\OneDrive\Desktop\Learning\01\ Firmware\02\ Udemy\ -\ FreeRTOS\workspace\006TaskNotifyFromISR\STM32F429ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "006TaskNotifyFromISR.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pubud\OneDrive\Desktop\Learning\01 Firmware\02 Udemy - FreeRTOS\workspace\006TaskNotifyFromISR\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="006TaskNotifyFromISR.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

006TaskNotifyFromISR.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "006TaskNotifyFromISR.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 006TaskNotifyFromISR.elf 006TaskNotifyFromISR.list 006TaskNotifyFromISR.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
