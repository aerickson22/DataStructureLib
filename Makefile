# Build mode: release (default) or debug
#   make                    -> optimized release build
#   make BUILD=debug test   -> sanitizers + -Werror, then run the tests
BUILD ?= release
WARN   = -Wall -Wextra

# Compiler and flags
CC = gcc
ifeq ($(BUILD),debug)
  CFLAGS = $(WARN) -Werror -g -O0 -fsanitize=address,undefined
else ifeq ($(BUILD),release)
  CFLAGS = $(WARN) -O2 -DNDEBUG
else
  $(error BUILD must be 'release' or 'debug', got '$(BUILD)')
endif

# Install location (override with: make install PREFIX=$HOME/.local)
PREFIX ?= /usr/local

# Directories (each mode gets its own, so builds never collide)
SRC_DIR      = src
OBJ_DIR      = obj/$(BUILD)
BIN_DIR      = bin/$(BUILD)
TEST_DIR     = test
TEST_BIN_DIR = $(BIN_DIR)/tests

# Files
TARGET  = $(BIN_DIR)/libds_lib.a
SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Test files: every test/*_test.c becomes its own executable in bin/<mode>/tests/
TEST_SRCS  = $(wildcard $(TEST_DIR)/*_test.c)
TEST_BINS  = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRCS))

# Default target
all: $(TARGET)

# Archive objects into a static library
$(TARGET): $(OBJS) | $(BIN_DIR)
	ar rcs $@ $^

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build a test executable
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJS) | $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $< $(OBJS) -o $@

# Create dirs if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TEST_BIN_DIR):
	mkdir -p $(TEST_BIN_DIR)

# Run all tests (use BUILD=debug to catch leaks and memory errors)
test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "==> $$t"; \
		./$$t || exit 1; \
	done
	@echo "All tests passed"

# Install library and headers (always installs the release build)
install:
	$(MAKE) BUILD=release all
	install -d $(DESTDIR)$(PREFIX)/lib $(DESTDIR)$(PREFIX)/include/ds_lib
	install -m 644 bin/release/libds_lib.a $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(SRC_DIR)/*.h $(DESTDIR)$(PREFIX)/include/ds_lib/

# Remove installed files
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/libds_lib.a
	rm -rf $(DESTDIR)$(PREFIX)/include/ds_lib

# Clean (removes both release and debug builds)
clean:
	rm -rf obj bin

# Rebuild
re: clean all

.PHONY: all clean re test install uninstall
