CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-gcc
GDB = arm-none-eabi-gdb
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size



SFLAGS += -Wnarrowing

#SFLAGS += -ffreestanding -nostdinc -nostdlib
#include liba/Makefile
#include libaxx/Makefile

#INCLUDE	= $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
#          -I$(CURDIR)/$(BUILD)

CFLAGS += -mtune=arm926ej-s -mcpu=arm926ej-s -marm -D_EVM -Wnarrowing

CXXFLAGS = $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11 -Wnarrowing

LIBS = -lm

#LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

LDFLAGS += -Wl,--gc-sections


LDFLAGS += $(SFLAGS) -lm -lgcc -lstdc++ -nostartfiles -Wl,-T,$(LDSCRIPT)
# -lc   -lgcc -lstdc++