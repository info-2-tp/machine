################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Firmware/KitInfo2FW_7Seg.c \
../Firmware/KitInfo2FW_Entradas.c \
../Firmware/KitInfo2FW_Inicializacion.c \
../Firmware/KitInfo2FW_Teclado.c \
../Firmware/KitInfo2FW_TimerTick.c \
../Firmware/KitInfo2FW_lcd.c \
../Firmware/cr_startup_lpc175x_6x.c \
../Firmware/crp.c 

OBJS += \
./Firmware/KitInfo2FW_7Seg.o \
./Firmware/KitInfo2FW_Entradas.o \
./Firmware/KitInfo2FW_Inicializacion.o \
./Firmware/KitInfo2FW_Teclado.o \
./Firmware/KitInfo2FW_TimerTick.o \
./Firmware/KitInfo2FW_lcd.o \
./Firmware/cr_startup_lpc175x_6x.o \
./Firmware/crp.o 

C_DEPS += \
./Firmware/KitInfo2FW_7Seg.d \
./Firmware/KitInfo2FW_Entradas.d \
./Firmware/KitInfo2FW_Inicializacion.d \
./Firmware/KitInfo2FW_Teclado.d \
./Firmware/KitInfo2FW_TimerTick.d \
./Firmware/KitInfo2FW_lcd.d \
./Firmware/cr_startup_lpc175x_6x.d \
./Firmware/crp.d 


# Each subdirectory must supply rules for building sources it contributes
Firmware/%.o: ../Firmware/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\BUBU\Documents\Expansion3\src" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


