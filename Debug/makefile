################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SnakeGame_003.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SnakeGame_003.list \

OBJCOPY_BIN += \
SnakeGame_003.bin \


# All Target
all: SnakeGame_003.elf secondary-outputs

# Tool invocations
SnakeGame_003.elf: $(OBJS) $(USER_OBJS) /Users/nasri/Nasri/University/Year2_Semster2/Embedded_Lab/Workspace_001/SnakeGame_003/STM32F411RETX_FLASH.ld
	arm-none-eabi-gcc -o "SnakeGame_003.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/nasri/Nasri/University/Year2_Semster2/Embedded_Lab/Workspace_001/SnakeGame_003/STM32F411RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SnakeGame_003.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SnakeGame_003.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SnakeGame_003.list"
	@echo 'Finished building: $@'
	@echo ' '

SnakeGame_003.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SnakeGame_003.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
