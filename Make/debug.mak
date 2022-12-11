BINARYDIR := Debug

#Optimization
OPT = -O3 -finline-functions

C_SOURCES += 

CPP_SOURCES += 

#Additional flags
PREPROCESSOR_MACROS += __DEBUG_SRAM__ __RTT_ENABLE__
C_INCLUDE_DIRS += 
LIBRARY_DIRS += 
LIBRARY_NAMES += 
ADDITIONAL_LINKER_INPUTS += 
 

C_FLAGS += -g -gdwarf-2
CPP_FLAGS += -g -gdwarf-2
AS_FLAGS += 
LD_FLAGS += -Wl,-gc-sections
LINKER_SCRIPT := ../LinkerScripts/GCC/CH32V307_flash.lds

GENERATE_BIN_FILE := 0
GENERATE_IHEX_FILE := 0
GENERATE_MAP_FILE := 1
