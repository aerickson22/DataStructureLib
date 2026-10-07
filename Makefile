# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g

# Directories
SRC_DIR      = src
OBJ_DIR      = obj
BIN_DIR      = bin
TEST_DIR     = test
TEST_BIN_DIR = $(BIN_DIR)/tests

# Files
TARGET  = $(BIN_DIR)/ds_lib
SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Test files: every test/*.c becomes its own executable in bin/tests/
# main.o is excluded so a test's own main() doesn't clash with yours
LIB_OBJS   = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
TEST_SRCS  = $(wildcard $(TEST_DIR)/*_test.c)
TEST_BINS  = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRCS))

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build a test executable
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB_OBJS) | $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -fsanitize=address -I$(SRC_DIR) $< $(LIB_OBJS) -o $@

# Create dirs if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

# Run all tests
test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "==> $$t"; \
		./$$t || exit 1; \
	done
	@echo "All tests passed"

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild
re: clean all

# Run
run: all
	./$(TARGET)

.PHONY: all clean re run test
