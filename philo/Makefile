# Compiler and Flags
CC = gcc
CFLAGS_RELEASE_SAFE = -Iinclude -Wall -Wextra -O2
CFLAGS_RELEASE_FAST = -Iinclude -Wall -Wextra -O3 -mtune=native
CFLAGS_DEBUG = -Iinclude -Wall -Wextra -g3 -fno-omit-frame-pointer -fsanitize=address
# CFLAGS_DEBUG = -Iinclude -Wall -Wextra -g3 -fsanitize=thread

# Linking Flags
LDFLAGS_RELEASE_SAFE = -lpthread
LDFLAGS_RELEASE_FAST = -lpthread
LDFLAGS_DEBUG = -lpthread

# Directories
LIBRARY_DIR = library
SRC_DIR = src
OBJ_DIR = $(LIBRARY_DIR)/.obj

# Target Executable
TARGET = philo

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Libraries
LIBS = $(LIBRARY_DIR)/libslib.a

# Progress Tracker
TOTAL := $(words $(SRCS))
CURRENT := 0

.PHONY: all clean fclean re debug release_safe release_fast

.DEFAULT_GOAL := debug

all: CFLAGS = $(CFLAGS_DEBUG)
all: LDFLAGS = $(LDFLAGS_DEBUG)
all: $(TARGET)

debug: CFLAGS = $(CFLAGS_DEBUG)
debug: LDFLAGS = $(LDFLAGS_DEBUG)
debug: $(TARGET)

release_safe: CFLAGS = $(CFLAGS_RELEASE_SAFE)
release_safe: LDFLAGS = $(LDFLAGS_RELEASE_SAFE)
release_safe: $(TARGET)

release_fast: CFLAGS = $(CFLAGS_RELEASE_FAST)
release_fast: LDFLAGS = $(LDFLAGS_RELEASE_FAST)
release_fast: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):
	$(MAKE) -s -C $(LIBRARY_DIR)

clean:
	@$(MAKE) -s -C $(LIBRARY_DIR) clean 
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -s -C $(LIBRARY_DIR) fclean 
	@rm -f $(TARGET)

re: fclean all
