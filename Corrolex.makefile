# Makefile for Corrolex-X Project

# Compiler and flags
CC = corx
CFLAGS = -O2 -Wall

# Paths
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
PACKAGE_DIR = package

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.corx)
OBJS = $(SRCS:$(SRC_DIR)/%.corx=$(BUILD_DIR)/%.o)

# Target
TARGET = $(BIN_DIR)/corrolex-x

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
    @mkdir -p $(BIN_DIR)
    $(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.corx
    @mkdir -p $(BUILD_DIR)
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -rf $(BUILD_DIR) $(BIN_DIR)

package: $(TARGET)
    @mkdir -p $(PACKAGE_DIR)
    cp -r $(BIN_DIR) $(PACKAGE_DIR)

.PHONY: all clean package
