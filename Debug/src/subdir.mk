################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/main.o 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	aarch64-tdx-linux-g++ -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/include -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/lib/glib-2.0/include -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/include/glib-2.0 -I/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/include/gstreamer-1.0/ -O0 -g3 -Wall -c -fmessage-length=0 --sysroot=/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux `/opt/tdx-xwayland/6.5.0/sysroots/x86_64-tdxsdk-linux/usr/bin/pkg-config --libs gstreamer-1.0 glib-2.0` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


