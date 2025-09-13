CC := clang
CFLAGS := -std=c11 -O2 -Wall -Wextra -pedantic
LDFLAGS := -lm

SRC_DIR := eleml
TEST_DIR := tests
BUILD_DIR := .build

# Find all source files under eleml
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Test sources mirror the src tree under tests/
TEST_SRCS := $(shell find $(TEST_DIR) -name 'test_*.c')
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%,$(TEST_SRCS))

.PHONY: all test clean clobber dirs

all: dirs $(OBJS)

dirs:
	mkdir -p $(BUILD_DIR)

# Object files for library compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

# Link each test with all src objects
$(BUILD_DIR)/%: $(TEST_DIR)/%.c $(OBJS) | dirs
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $< $(OBJS) -o $@ $(LDFLAGS)

test: $(TEST_BINS)
	@set -e; \
	for t in $(TEST_BINS); do \
	  echo "==> $$t"; \
	  $$t; \
	done

clean:
	rm -rf $(BUILD_DIR)

clobber: clean
	rm -rf $(BUILD_DIR)

