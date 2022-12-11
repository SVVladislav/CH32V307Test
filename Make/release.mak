BINARYDIR := Release

#Optimization
OPT = -Os -flto -finline-functions

C_SOURCES += 

CPP_SOURCES += 

#Additional flags
PREPROCESSOR_MACROS += 
C_INCLUDE_DIRS += 
LIBRARY_DIRS += 
LIBRARY_NAMES += 
ADDITIONAL_LINKER_INPUTS += 
 

C_FLAGS += -gdwarf-2
CPP_FLAGS += -gdwarf-2
AS_FLAGS += 
LD_FLAGS += -Wl,-gc-sections
LINKER_SCRIPT := ../LinkerScripts/GCC/CH32V307_flash.lds

GENERATE_BIN_FILE := 1
GENERATE_IHEX_FILE := 1
GENERATE_MAP_FILE :=1
