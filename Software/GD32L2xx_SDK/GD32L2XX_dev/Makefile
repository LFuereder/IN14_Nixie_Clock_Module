
#Target
TARGET = GD32L2xx

# Build path
BUILD_DIR = build

# C sources
C_SOURCES = \
./GD32_startup.c \
$(wildcard src/*.c) \
$(wildcard lib/src/*.c)

# ASM sources
ASM_SOURCES =  

#Compilershit
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc -x assembler-with-cpp

BIN = arm-none-eabi-objcopy -O binary -S

# C defines
C_DEFS = 

# C includes
C_INCLUDES =  \
-Iinc \
-Ilib/inc \
-ICMSIS/Core/Include
# mcu
MCU = -mcpu=cortex-m23 -march=armv8-m.base -mthumb

#flags
ASFLAGS = $(MCU) -Og -Wall -fdata-sections -ffunction-sections
CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) -Og -Wall -fdata-sections -ffunction-sections -g -gdwarf-2

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# link script
LDSCRIPT = GD32L2xx.ld

# libraries
LIBS = -lc -lm -lnosys 

LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

#########################################################
.PHONY: clean, new, default, VisualFeedback
default: all VisualFeedback

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf | $(BUILD_DIR)
	$(BIN) $< $@


clean:
	rm -f $(BUILD_DIR)/*

new: clean default

#VisualFeedback:
#	@echo "______         _  _      _           _____                                      __         _  _ "
#	@echo "| ___ \       (_)| |    | |         /  ___|                                    / _|       | || |"
#	@echo "| |_/ / _   _  _ | |  __| |  ______ \ `--.  _   _   ___   ___   ___  ___  ___ | |_  _   _ | || |"
#	@echo "| ___ \| | | || || | / _` | |______| `--. \| | | | / __| / __| / _ \/ __|/ __||  _|| | | || || |"
#	@echo "| |_/ /| |_| || || || (_| |         /\__/ /| |_| || (__ | (__ |  __/\__ \\__ \| |  | |_| || || |"
#	@echo "\____/  \__,_||_||_| \__,_|         \____/  \__,_| \___| \___| \___||___/|___/|_|   \__,_||_||_|"
                                                                                                
                                       
-include $(wildcard $(BUILD_DIR)/*.d)

