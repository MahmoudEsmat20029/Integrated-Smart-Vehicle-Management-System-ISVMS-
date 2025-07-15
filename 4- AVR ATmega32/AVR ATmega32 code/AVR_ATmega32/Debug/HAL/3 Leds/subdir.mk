################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/3\ Leds/leds.c 

OBJS += \
./HAL/3\ Leds/leds.o 

C_DEPS += \
./HAL/3\ Leds/leds.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/3\ Leds/leds.o: ../HAL/3\ Leds/leds.c HAL/3\ Leds/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"HAL/3 Leds/leds.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


