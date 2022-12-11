SET GIT_LIB_DIR=d:\!Projects\GIT-STM32\stm32-libs

rd Src\Inc\Hardware  /s /q
rd Src\Inc\SVVTL  /s /q
mklink /D /J Src\Inc\Hardware "%GIT_LIB_DIR%\Hardware"
mklink /D /J Src\Inc\SVVTL "%GIT_LIB_DIR%\SVVTL"
rem del mk_links.bat /q
pause