# Project directory structure
BIN := bin
SRC := src
LIB := lib
INC := include
MAINFILE := $(SRC)/main.cpp


# Build directories and output
TARGET := $(BIN)/main
BUILD := build


# Compiler
CXX := g++

# Pre-compiler and Compiler flags
CXX_FLAGS := -Wall -Wextra -ggdb

# Library search directories and flags
EXT_LIB :=
LDFLAGS :=
LDPATHS := $(addprefix -L,$(LIB) $(EXT_LIB))

# Include directories
INC_DIRS := $(INC) $(shell find $(SRC) -type d) 
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


# Source and Object files
SRCS := $(shell find $(SRC) -name "*.cpp")
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))


# Run task
run: build
	echo "Executing ..."
	./$(TARGET) $(ARGS)


# Build task
build: clean all

# Main task
all: $(TARGET)

# Task producing target from build files
$(TARGET): $(OBJS)
	@echo "Building..."
	mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDPATHS) $(LDFLAGS)


# Compile all cpp files
$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c -o $@ $< $(LDPATHS) $(LDFLAGS)
 
# Clean task
.PHONY: clean
clean:
	@echo "Clearing..."
	rm -rf build
