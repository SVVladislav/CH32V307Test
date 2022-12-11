TOOLCHAIN_ROOT = /opt/xpack-riscv-none-elf-gcc-12.2.0-1/bin
PREFIX = riscv-none-elf-

CC = $(TOOLCHAIN_ROOT)/$(PREFIX)gcc
CPP = $(TOOLCHAIN_ROOT)/$(PREFIX)g++
AS = $(TOOLCHAIN_ROOT)/$(PREFIX)gcc -x assembler-with-cpp
LD = $(CXX)
AR = $(TOOLCHAIN_ROOT)/$(PREFIX)ar
OBJCOPY = $(TOOLCHAIN_ROOT)/$(PREFIX)objcopy
SZ = $(TOOLCHAIN_ROOT)/$(PREFIX)size
MD = mkdir -p

HEX = $(OBJCOPY) -O ihex
BIN = $(OBJCOPY) -O binary -S
