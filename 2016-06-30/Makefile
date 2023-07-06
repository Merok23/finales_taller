# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

# Directories
OBJ_DIR := obj
TARGET_DIR := target

# Source files
SOURCES := $(wildcard *.cpp *.c)
OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES)))
TARGET := $(TARGET_DIR)/program

# Main target
all: $(TARGET)

# Rule to create object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files and create the final target
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET_DIR)

.PHONY: all clean
