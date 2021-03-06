#Main Makefile
CC := gcc
CFLAGS := -g -Wall -MMD

#Binary
ifeq ($(OS),Windows_NT)
    BIN := main.exe
	DLE := dll
	LIBRARIES = -municode
else
    BIN := main.out
	DLE := so
endif

#Directories
IDIR := ./include
SDIR := ./src

ifeq ($(OS),Windows_NT)
	ODIR := ./obj/windows
else
	ODIR := ./obj/linux
endif

#Libraries
LIBS := libpcre2-8
CFLAGS += `pkg-config --cflags $(LIBS)`
LIBRARIES += `pkg-config --libs $(LIBS)`

#Files
SOURCE := .c

#Paths
INCLUDE_PATHS := -I$(IDIR)

#Compilation line
COMPILE := $(CC) $(CFLAGS) $(INCLUDE_PATHS)

#FILEs
#---------------Source----------------#
SRCS := $(wildcard $(SDIR)/*$(SOURCE))

#---------------Object----------------#
OBJS := $(SRCS:$(SDIR)/%$(SOURCE)=$(ODIR)/%.o)
#-------------Dependency--------------#
DEPS := $(SRCS:$(SDIR)/%$(SOURCE)=$(ODIR)/%.d)

all: dll

test: $(OBJS)
	$(COMPILE) $(OBJS) main$(SOURCE) -o $(BIN) $(LIBRARIES)

dll: LIBRARIES += -lm -fPIC
dll: LIB_NAME := str-utils
dll: $(OBJS)
	$(COMPILE) -shared -o lib$(LIB_NAME).$(DLE) $(OBJS) $(LIBRARIES)

# Include all .d files
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%$(SOURCE)
	$(COMPILE) -c $< -o $@ $(LIBRARIES)

.PHONY : clean
clean :
	-rm $(BIN) $(OBJS) $(DEPS)
