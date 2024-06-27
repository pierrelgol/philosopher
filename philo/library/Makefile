# Compiler and Flags
CC = clang
CFLAGS_RELEASE_SAFE = -Iinclude -Wall -Wextra -O2 
CFLAGS_RELEASE_FAST = -Iinclude -Wall -Wextra -O3 -mtune=native
CFLAGS_DEBUG = -Iinclude -Wall -Wextra -g3 -fno-omit-frame-pointer

# Project Structure
SRC_DIR = src
OBJ_DIR = .obj
INCLUDE_DIR = include
TARGET_LIB = libslib.a
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Progress Tracker
TOTAL := $(words $(SRCS))
CURRENT := 0

define PRINT_PROGRESS
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@PROGRESS=$$(echo "scale=2; 100 * $(CURRENT) / $(TOTAL)" | bc -l); \
	if [ $(CURRENT) -le $(TOTAL) ]; then \
		printf "\r\033[K\033[1;34m[\033[0m"; \
		BAR_SIZE=$$(echo "$$PROGRESS / 2" | bc); \
		for i in $$(seq 1 50); do \
			if [ $$BAR_SIZE -ge $$i ]; then \
				printf "\033[1;32m#\033[0m"; \
			else \
				printf " "; \
			fi; \
		done; \
		printf "\033[1;34m] %.2f%%\033[0m" $$PROGRESS; \
	fi
endef

.PHONY: all clean fclean re debug release_safe release_fast

# Default Target
.DEFAULT_GOAL := debug

# Default Target (debug)
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: $(TARGET_LIB)

# Release Safe Build
release_safe: CFLAGS = $(CFLAGS_RELEASE_SAFE)
release_safe: $(TARGET_LIB)

# Release Fast Build
release_fast: CFLAGS = $(CFLAGS_RELEASE_FAST)
release_fast: $(TARGET_LIB)

# Build Library
$(TARGET_LIB): $(OBJS)
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call PRINT_PROGRESS)

# Clean Up
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(TARGET_LIB)

# Rebuild
re: fclean all

# Target Aliases
all: debug
