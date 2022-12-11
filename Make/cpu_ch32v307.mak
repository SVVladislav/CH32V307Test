######################################
# CPU Settings
######################################
CPU = -march=rv32imafc -mabi=ilp32f
FPU = 
FLOAT-ABI = 
MCU = $(CPU) $(FPU) $(FLOAT-ABI)
