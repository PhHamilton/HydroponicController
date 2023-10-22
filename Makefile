# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall

# Directories
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

HEADERS := $(wildcard $(INC_DIR)/*.h)

# Target executable

ifeq ($(UC),1)
    OBJS := $(filter-out $(OBJ_DIR)/unit_tests.o, $(OBJS))
	TARGET := out
else
    # Include unit_tests.cpp
    OBJS := $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	TARGET := test
endif

# Compile and link
$(TARGET): $(OBJS)
	rm -f $(TARGET)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $^ -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(dir $<) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean

