################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: SplashScreen

# Tool invocations
SplashScreen: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	aarch64-tdx-linux-g++ -L/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux/usr/lib/ --sysroot=/opt/tdx-xwayland/6.5.0/sysroots/cortexa72-cortexa53-tdx-linux `/opt/tdx-xwayland/6.5.0/sysroots/x86_64-tdxsdk-linux/usr/bin/pkg-config --libs gstreamer-1.0 gobject-2.0 glib-2.0` -o "SplashScreen" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) SplashScreen
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
