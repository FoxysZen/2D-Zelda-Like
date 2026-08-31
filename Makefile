TARGET = zelda-like

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

LIBS = -lSDL2 -lSDL2_image

SRC_DIR = src
BUILD_DIR = build

SRCS = $(shell find $(SRC_DIR) -name '*.cc')
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)
	@echo "Compiled!"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
