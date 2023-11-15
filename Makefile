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

# Default target is "out"
TARGET := out

# If "test" is specified as a make target, update the target and object files
ifeq ($(MAKECMDGOALS),test)
    TARGET := test
    OBJS := $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
    OBJS := $(filter-out $(OBJ_DIR)/ads1015.o, $(OBJS))
    OBJS := $(filter-out $(OBJ_DIR)/i2cHandler.o, $(OBJS))
    OBJS := $(filter-out $(OBJ_DIR)/waterlevel.o, $(OBJS))
endif

# If "uc" is specified as a make target, update the target and object files
ifeq ($(MAKECMDGOALS),uc)
    TARGET := out
    OBJS := $(filter-out $(OBJ_DIR)/unit_tests.o, $(OBJS))
    OBJS := $(filter-out $(OBJ_DIR)/waterlevel.o, $(OBJS))
endif

ifeq ($(MAKECMDGOALS), waterlevel)
    TARGET := waterlevel
    OBJS := $(filter-out $(OBJ_DIR)/unit_tests.o, $(OBJS))
    OBJS := $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	CXXFLAGS += -pthread
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

