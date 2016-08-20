############ create by wuxx #############

#from build_sos.sh
CFLAGS = $(cflags)
#$(warning CFLAGS: $(CFLAGS))
HOST_IS_ARM = $(shell uname -m | grep "arm")

#$(warning HOST_IS_ARM: $(HOST_IS_ARM))
ifeq ("", $(HOST_IS_ARM))
    TOOLCHAIN_DIR=$(ROOT)/.compiler
    CROSS_COMPILE=$(TOOLCHAIN_DIR)/bin/arm-none-eabi-
    LIBGCC = $(shell find $(TOOLCHAIN_DIR)/ | grep "armv6-m\/libgcc\.a")
endif

LIBGCC ?= $(shell gcc -print-libgcc-file-name)
#$(warning libgcc $(LIBGCC))

ROOT = .

CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
READELF = $(CROSS_COMPILE)readelf

BUILD = $(ROOT)/build

PLATFORM_DIR = $(ROOT)/platform/rpi_b
DRIVER_DIR   = $(ROOT)/driver
LIBC_DIR     = $(ROOT)/libc
SHELL_DIR    = $(ROOT)/shell
INCLUDE_DIR  = $(ROOT)/include

PLATFORM_SRCS =  \
		$(PLATFORM_DIR)/main.c      \
		$(PLATFORM_DIR)/init.s      \
		$(PLATFORM_DIR)/arm_v6.s

LIBC_SRCS =  \
		$(LIBC_DIR)/libc.c

DRIVER_SRCS = \
		$(DRIVER_DIR)/timer/timer.c             \
		$(DRIVER_DIR)/watchdog/watchdog.c       \
		$(DRIVER_DIR)/uart/uart.c

SHELL_SRCS = \
		$(SHELL_DIR)/shell.c           \
		$(SHELL_DIR)/cmd_ymodem.c

ALL_SRCS = $(PLATFORM_SRCS) $(LIBC_SRCS) $(DRIVER_SRCS) $(SHELL_SRCS)

C_SRCS   = $(filter %.c, $(ALL_SRCS))
ASM_SRCS = $(filter %.s, $(ALL_SRCS)) 
H_SRCS   = $(wildcard $(INCLUDE_DIR)/*.h)

C_OBJS   = $(addprefix $(BUILD)/, $(patsubst %.c,%.o,$(C_SRCS)))
ASM_OBJS = $(addprefix $(BUILD)/, $(patsubst %.s,%.o,$(ASM_SRCS)))

ALL_OBJS = $(C_OBJS) $(ASM_OBJS)
#$(warning ALL_SRCS $(ALL_SRCS))
#$(warning ALL_OBJS $(ALL_OBJS))

#$(warning C_SRCS $(C_SRCS) ASM_SRCS $(ASM_SRCS))
#$(warning C_OBJS $(C_OBJS) ASM_OBJS $(ASM_OBJS))


OBJ_PATHS = $(addprefix $(BUILD)/, $(sort $(dir $(ALL_SRCS))))
#$(warning OBJ_PATHS $(OBJ_PATHS))


TARGET = sboot
TARGET_ELF = $(BUILD)/$(TARGET).elf
TARGET_IMG = $(BUILD)/$(TARGET).img
TARGET_MAP = $(BUILD)/$(TARGET).map
TARGET_DISASM = $(BUILD)/$(TARGET).disasm
TARGET_ELFINFO = $(BUILD)/$(TARGET).elfinfo
TARGET_SECINFO = $(BUILD)/$(TARGET).secinfo #section info

LDS = $(ROOT)/$(TARGET).ld

#-march=armv6
CFLAGS  += -mcpu=arm1176jzf-s -fno-builtin -mno-thumb-interwork -mfloat-abi=soft -Wall -g -I$(INCLUDE_DIR)
ASFLAGS += -mcpu=arm1176jzf-s 

LDFLAGS = -T $(LDS) -Map $(TARGET_MAP) -nostdlib -nostartfiles $(LIBGCC) 

.PHONY: build_all clean tags

build_all: all

$(C_OBJS): $(H_SRCS)
$(C_OBJS): $(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJS): $(BUILD)/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

build_objs: $(C_OBJS) $(ASM_OBJS)

init:
	mkdir -p build
	$(foreach d,$(OBJ_PATHS), mkdir -p $(d);)

all:init build_objs
	$(LD) $(ALL_OBJS) $(LDFLAGS) -o $(TARGET_ELF)
	$(OBJCOPY) $(TARGET_ELF) -O binary $(TARGET_IMG)
	$(OBJDUMP) -S $(TARGET_ELF) > $(TARGET_DISASM)
	$(OBJDUMP) -s $(TARGET_ELF) > $(TARGET_SECINFO)
	$(READELF) -a $(TARGET_ELF) > $(TARGET_ELFINFO)

tags:
	ctags -R $(KERNEL_DIR) $(SYSTEM_DIR) $(LIBC_DIR) $(DRIVER_DIR) $(TEST_DIR) $(INCLUDE_DIR)
	#find ./driver ./libc ./include ./system ./test | grep ".*\.[ch]$$" | xargs wc -l

clean: 
	-rm -rf build
