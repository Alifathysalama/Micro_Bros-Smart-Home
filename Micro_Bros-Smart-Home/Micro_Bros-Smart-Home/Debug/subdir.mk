################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../KeyPad.c \
../LCD.c \
../PIR.c \
../TEMP.c \
../main.c \
../motor.c 

OBJS += \
./Buzzer.o \
./KeyPad.o \
./LCD.o \
./PIR.o \
./TEMP.o \
./main.o \
./motor.o 

C_DEPS += \
./Buzzer.d \
./KeyPad.d \
./LCD.d \
./PIR.d \
./TEMP.d \
./main.d \
./motor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


