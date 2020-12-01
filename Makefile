# Default rule is 'all'
.DEFAULT_GOAL	:=	all

# Parameters to configure compilation
# TARGET: Name of output file
# BUILD: Directory to store build files
# INCLUDE: Folder to include headers from
# SOURCE: Folder to include source files from
# LIBS: Libraries to link against
TARGET		:=	LEDrum
BUILD		:=	build
INCLUDE		:=	include
SOURCE		:=	source
LIBS		:=	-lpigpio -lpthread -lrt

# Flags to pass to the compiler
CXXFLAGS	:=	-std=c++17 -Wall -O2 -fno-exceptions -fno-rtti -I$(CURDIR)/$(INCLUDE)
LD		:=	$(CXX)

# Derive subfolders based on above configuration
DEPDIR		:=	$(BUILD)/deps
OBJDIR		:=	$(BUILD)/objs

# Find files in folders specified in above configuration
CPPFILES	:=	$(shell find $(SOURCE)/ -name "*.cpp")
DEPS		:=	$(filter %.d, $(CPPFILES:$(SOURCE)/%.cpp=$(DEPDIR)/%.d))
OFILES		:=	$(filter %.o, $(CPPFILES:$(SOURCE)/%.cpp=$(OBJDIR)/%.o))
TREE		:=	$(sort $(patsubst %/,%,$(dir $(OFILES))))

# Include dependent files if they exist
ifeq "$(MAKECMDGOALS)" ""
-include $(DEPS)
endif

# Define our virtual targets
.PHONY: all clean

# 'all' compiles the final binary from object files
all:		$(TARGET)
$(TARGET):	$(OFILES)
	@echo Linking $(TARGET)...
	@$(LD) $(OFILES) $(LIBS) -o $@

# 'clean' removes all build files
clean:
	@echo Cleaning build files...
	@rm -rf $(BUILD) $(TARGET)

# This magically compiles each object file
.SECONDEXPANSION:
$(OBJDIR)/%.o:	$(SOURCE)/%.cpp | $$(@D)
	@echo Compiling $*.o...
	@$(CXX) -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d) -o $@ $(CXXFLAGS) -c $<

# '$(TREE)' creates directories in the build directory
$(TREE): 	%:
	@mkdir -p $@
	@mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)
