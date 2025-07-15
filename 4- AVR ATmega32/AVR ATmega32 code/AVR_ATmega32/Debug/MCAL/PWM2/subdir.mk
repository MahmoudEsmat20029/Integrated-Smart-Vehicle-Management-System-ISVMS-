################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/PWM2/PWM2.c 

OBJS += \
./MCAL/PWM2/PWM2.o 

C_DEPS += \
./MCAL/PWM2/PWM2.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/PWM2/%.o: ../MCAL/PWM2/%.c MCAL/PWM2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


