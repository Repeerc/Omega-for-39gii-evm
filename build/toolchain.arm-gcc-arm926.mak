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

CXXFLAGS = -mtune=arm926ej-s -mcpu=arm926ej-s -marm -D_EVM -std=gnu++11 -fno-exceptions -fno-rtti -fno-threadsafe-statics
# -std=gnu++11
LIBS = -lm

#LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

LDFLAGS += -Wl,--gc-sections


LDFLAGS += $(SFLAGS) -lc -lm -lstdc++ -nostartfiles -Wl,-T,$(LDSCRIPT)
# -lc   -lgcc -lstdc++