################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/events.c \
../src/main.c \
../src/probando.c \
../src/queues.c \
../src/semaphores.c 

OBJS += \
./src/events.o \
./src/main.o \
./src/probando.o \
./src/queues.o \
./src/semaphores.o 

C_DEPS += \
./src/events.d \
./src/main.d \
./src/probando.d \
./src/queues.d \
./src/semaphores.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -D__NEWLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


