################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c \
../utilities/fsl_io.c \
../utilities/fsl_log.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_io.o \
./utilities/fsl_log.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_io.d \
./utilities/fsl_log.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=0 -D__USE_CMSIS -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -DDEBUG -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCPU_MK64FN1M0VLL12_cm4 -DCPU_MK64FN1M0VLL12 -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1\board" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1\source" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1\drivers" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1\CMSIS" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1\utilities" -I"C:\Users\Robin\Documents\MCUXpressoIDE_10.1.1_606\workspace\Clase-1\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


