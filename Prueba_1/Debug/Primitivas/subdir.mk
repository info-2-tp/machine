################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/KitInfo2AP_Pruebas.c \
../Primitivas/KitInfo2PR_7Seg.c \
../Primitivas/KitInfo2PR_Teclado.c \
../Primitivas/KitInfo2PR_Timer.c \
../Primitivas/KitInfo2PR_gpio.c \
../Primitivas/KitInfo2PR_lcd.c 

OBJS += \
./Primitivas/KitInfo2AP_Pruebas.o \
./Primitivas/KitInfo2PR_7Seg.o \
./Primitivas/KitInfo2PR_Teclado.o \
./Primitivas/KitInfo2PR_Timer.o \
./Primitivas/KitInfo2PR_gpio.o \
./Primitivas/KitInfo2PR_lcd.o 

C_DEPS += \
./Primitivas/KitInfo2AP_Pruebas.d \
./Primitivas/KitInfo2PR_7Seg.d \
./Primitivas/KitInfo2PR_Teclado.d \
./Primitivas/KitInfo2PR_Timer.d \
./Primitivas/KitInfo2PR_gpio.d \
./Primitivas/KitInfo2PR_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/%.o: ../Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\BUBU\Documents\Expansion3\src" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


