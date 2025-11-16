CC = gcc
CFLAGS = -Wextra -Wall -g
INCLUDE_DIR = include

SOURCES = main.c \
          $(INCLUDE_DIR)/ast.c \
          $(INCLUDE_DIR)/parser.c \
          $(INCLUDE_DIR)/token.c \
          $(INCLUDE_DIR)/codegen.c

BUILD_DIR = build
COMPILER = $(BUILD_DIR)/main
ASM_FILE = output.s
OUTPUT = $(BUILD_DIR)/output

all: $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SOURCES) -o $(COMPILER)
	@echo "Compiler built successfully at $(COMPILER)"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

compile: all
	./$(COMPILER)
	@echo "Generated $(ASM_FILE)"

assemble: $(BUILD_DIR)
	$(CC) $(ASM_FILE) -o $(OUTPUT)
	@echo "Assembled $(ASM_FILE) into $(OUTPUT)"

run:
	./$(OUTPUT)

clean:
	rm -rf $(BUILD_DIR) $(ASM_FILE)
	@echo "Cleaned build directory"

.PHONY: all compile assemble run clean
