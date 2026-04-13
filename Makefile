CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2

TARGET := $(notdir $(CURDIR))
BUILD_DIR := build

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

SRC_ALL := $(wildcard *.cpp *.hpp)

all: format $(BUILD_DIR)/$(TARGET)

# форматирование исходников
format:
	@if [ -n "$(SRC_ALL)" ]; then \
		clang-format -i $(SRC_ALL); \
	else \
		echo "Нет файлов для форматирования"; \
	fi

# линковка
$(BUILD_DIR)/$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@

# компиляция
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# создание build/
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean format
