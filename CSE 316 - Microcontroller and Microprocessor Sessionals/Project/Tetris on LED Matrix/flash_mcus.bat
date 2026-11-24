@echo off
setlocal

:: ==========================================
:: ATmega32 Build and Flash Script (Windows Batch)
:: ==========================================

set MCU=atmega32
set MCU_AVRDUDE=m32
set F_CPU=1000000UL
set PROGRAMMER=usbasp

if "%~1"=="1" goto build1
if "%~1"=="2" goto build2

:usage
echo Usage: flash_mcus.bat 1  (To compile and burn ATmega1_main.c)
echo Usage: flash_mcus.bat 2  (To compile and burn ATmega2_main.c)
exit /b 1

:build1
set TARGET=ATmega1_main
goto compile

:build2
set TARGET=ATmega2_main
goto compile

:compile

echo ==========================================
echo  Building and Flashing %TARGET% for %MCU%
echo ==========================================

:: 1. Compile
echo [1/3] Compiling %TARGET%.c...
avr-gcc -Wall -Os -std=gnu99 -DF_CPU=%F_CPU% -mmcu=%MCU% -o %TARGET%.elf %TARGET%.c
if %errorlevel% neq 0 (
    echo ERROR: Compilation failed!
    exit /b %errorlevel%
)

:: 2. Generate Hex
echo [2/3] Generating Hex File...
avr-objcopy -j .text -j .data -O ihex %TARGET%.elf %TARGET%.hex
if %errorlevel% neq 0 (
    echo ERROR: Hex generation failed!
    exit /b %errorlevel%
)

:: 3. Flash Code
echo [3/3] Flashing to ATmega32 using %PROGRAMMER%...
avrdude -p %MCU_AVRDUDE% -c %PROGRAMMER% -U flash:w:%TARGET%.hex:i
if %errorlevel% equ 0 (
    echo ==========================================
    echo  SUCCESS: %TARGET% flashed!
    echo ==========================================
) else (
    echo ==========================================
    echo  ERROR: Flashing failed. Check connections.
    echo ==========================================
    exit /b %errorlevel%
)
endlocal
