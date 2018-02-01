################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MK64FN1M0xxx12_Project0.c \
../source/semihost_hardfault.c 

OBJS += \
./source/MK64FN1M0xxx12_Project0.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/MK64FN1M0xxx12_Project0.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=0 -D__USE_CMSIS -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MK64FN1M0VLL12_cm4 -DCPU_MK64FN1M0VLL12 -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0\board" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0\source" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0\drivers" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0\CMSIS" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0\utilities" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\MK64FN1M0xxx12_Project0\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


