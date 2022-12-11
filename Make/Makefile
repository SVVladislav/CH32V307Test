# ------------------------------------------------
# Generic Makefile (based on gcc)
# ------------------------------------------------

to_lowercase = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

######################################
# Configurations 
######################################
# Common settings for all configurations
include common_settings.mak

COMMON_LINKER_SCRIPT := $(LINKER_SCRIPT)

CONFIG ?= RELEASE

CONFIGURATION_FLAGS_FILE := $(call to_lowercase,$(CONFIG)).mak

include $(CONFIGURATION_FLAGS_FILE)

CONFIGURATION_LINKER_SCRIPT := $(LINKER_SCRIPT)

# Configuration linker skript override common linker skript
ifeq ($(CONFIGURATION_LINKER_SCRIPT),)
LINKER_SCRIPT := $(COMMON_LINKER_SCRIPT)
endif

ifeq ($(OS),Windows_NT)
  BUILD_DIR := Bin\$(BINARYDIR)
  TOOL_CHAIN_MAK := toolchain_win.mak
else
  BUILD_DIR := Bin/$(BINARYDIR)
  TOOL_CHAIN_MAK := toolchain_lin.mak
endif

include $(TOOL_CHAIN_MAK)

# compile gcc flags
ASFLAGS = $(MCU) $(C_STANDART) $(addprefix -D,$(PREPROCESSOR_MACROS)) $(addprefix -I,$(C_INCLUDE_DIRS)) $(OPT) $(AS_FLAGS)
CFLAGS = $(MCU) $(C_STANDART) $(addprefix -D,$(PREPROCESSOR_MACROS)) $(addprefix -I,$(C_INCLUDE_DIRS)) $(OPT) $(C_FLAGS)
CPPFLAGS = $(MCU) $(CPP_STANDART) $(addprefix -D,$(PREPROCESSOR_MACROS)) $(addprefix -I,$(C_INCLUDE_DIRS)) $(OPT) $(CPP_FLAGS)

# Generate dependency information
AFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CPPFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# libraries
#LIBS = -lc -lm -lnosys

LDFLAGS = $(MCU) -T$(LINKER_SCRIPT) $(LIBDIR) $(LIBS) $(LD_FLAGS)

ifeq ($(GENERATE_MAP_FILE),1)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
endif

all_make_files := $(firstword $(MAKEFILE_LIST)) $(CONFIGURATION_FLAGS_FILE) common_settings.mak $(TOOL_CHAIN_MAK)

PRIMARY_OUTPUTS :=

ifeq ($(GENERATE_BIN_FILE),1)
PRIMARY_OUTPUTS += $(BUILD_DIR)/$(basename $(TARGET)).bin
endif

ifeq ($(GENERATE_IHEX_FILE),1)
PRIMARY_OUTPUTS += $(BUILD_DIR)/$(basename $(TARGET)).hex
endif

ifeq ($(PRIMARY_OUTPUTS),)
PRIMARY_OUTPUTS := $(BUILD_DIR)/$(TARGET).elf
endif

all: $(PRIMARY_OUTPUTS)


# default action: build all
#all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c $(all_make_files) | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp $(all_make_files) | $(BUILD_DIR) 
	$(CPP) -c $(CPPFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s $(all_make_files) | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) $(all_make_files)
	$(CPP) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	$(MD) $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***