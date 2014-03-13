################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../read_csv.cpp \
../train_model.cpp 

OBJS += \
./read_csv.o \
./train_model.o 

CPP_DEPS += \
./read_csv.d \
./train_model.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/sumit/opencv_2.4.7/opencv-2.4.7/include -I/home/sumit/opencv_2.4.7/opencv-2.4.7/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


