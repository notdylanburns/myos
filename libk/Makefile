CC := i686-elf-gcc
AR := i686-elf-ar

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SRC_DIR := $(ROOT_DIR)/src
INC_DIR := $(ROOT_DIR)/inc
OBJ_DIR := $(ROOT_DIR)/obj

DIRS := $(OBJ_DIR) $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(shell find $(SRC_DIR)/ -type d))

SRCS := $(shell find $(SRC_DIR)/ -type f)
OBJS := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%.o, $(basename $(SRCS)))

CFLAGS := -ffreestanding -O2 -Wall -Wextra -I$(INC_DIR)
ARFLAGS := rcs

TARGET := $(ROOT_DIR)/libk.a

libk: $(DIRS) $(TARGET)
$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRS):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

.PHONY: libk