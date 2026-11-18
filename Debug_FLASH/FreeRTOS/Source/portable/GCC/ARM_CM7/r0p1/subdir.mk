################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mpu_wrappers.c \
../FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mru_smp.c \
../FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mpu_wrappers.o \
./FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mru_smp.o \
./FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mpu_wrappers.d \
./FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mru_smp.d \
./FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/%.o: ../FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/mpu_wrappers.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


