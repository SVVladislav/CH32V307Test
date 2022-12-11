# Common for all configurations settings

######################################
# CPU
######################################
include cpu_ch32v307.mak

######################################
# target
######################################
TARGET = CH32V307

######################################
# sources
######################################

# C sources
C_SOURCES := \

# CPP sources
CPP_SOURCES := \
../Src/main.cpp \
../Src/low_level_init.cpp \
../Src/ch32v307_gcc_startup.cpp \

# ASM sources
ASM_SOURCES := \

######################################
# Compiler Settings
######################################

# C Standart
C_STANDART = -std=gnu11

# C++ Standart
CPP_STANDART = -std=gnu++1z

PREPROCESSOR_MACROS := 

######################################
# Includes
######################################
C_INCLUDE_DIRS := \
../Src/Inc \

LIBRARY_DIRS := 

LIBRARY_NAMES := 

ADDITIONAL_LINKER_INPUTS +=  

C_FLAGS := -ffunction-sections -fdata-sections -fno-exceptions -Wall

CPP_FLAGS := -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -Wall

AS_FLAGS = $(C_FLAGS)

LD_FLAGS := -Wl,--gc-sections -nostartfiles -specs=nano.specs -specs=nosys.specs

LINKER_SCRIPT := ../LinkerScripts/GCC/CH32V307_flash.lds 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group
