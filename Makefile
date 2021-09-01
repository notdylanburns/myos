CC := i686-elf-gcc
AS := i686-elf-as

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SRC_DIR := $(ROOT_DIR)/src
INC_DIR := $(ROOT_DIR)/inc
OBJ_DIR := $(ROOT_DIR)/obj
CFG_DIR := $(ROOT_DIR)/cfg

ISO_DIR := $(ROOT_DIR)/iso
BOOT_DIR := $(ISO_DIR)/boot
GRUB_DIR := $(BOOT_DIR)/grub

LINKCONF := $(CFG_DIR)/linker.ld
GRUBCONF := $(CFG_DIR)/grub.cfg
BUILDCONF := $(CFG_DIR)/build.cfg

DIRS := $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(sort $(shell awk '{ print $$2 }' $(BUILDCONF)))) $(ISO_DIR) $(BOOT_DIR) $(GRUB_DIR)

SRCS := $(shell find $(SRC_DIR)/ -type f)
OBJS := $(foreach src, $(SRCS), $(OBJ_DIR)/$(strip $(if $(shell grep '*$(suffix $(src))' $(BUILDCONF) | awk '{ print $$2 }'), $(shell grep '*$(suffix $(src))' $(BUILDCONF) | awk '{ print $$2 }')/,))$(addsuffix .o, $(basename $(notdir $(src)))))

CFLAGS := -ffreestanding -O2 -Wall -Wextra -I$(INC_DIR) -I$(ROOT_DIR)/libk/inc
LDFLAGS := -T $(LINKCONF) -ffreestanding -O2 -nostdlib -lgcc
ASFLAGS :=

LIBK := $(ROOT_DIR)/libk/libk.a
KERNEL_BIN := $(ROOT_DIR)/kernel.bin
TARGET := $(ROOT_DIR)/kernel.iso

kernel: $(DIRS) $(TARGET)
$(TARGET): $(KERNEL_BIN) validate isodir
	grub-mkrescue -o $@ $(ISO_DIR)

$(LIBK): 
	$(MAKE) -C libk

$(KERNEL_BIN): $(OBJS) $(LIBK)
	$(CC) $(LDFLAGS) -o $@ $^ 

$(OBJ_DIR)/asm/%.o: $(SRC_DIR)/asm/%.S
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/c/%.o: $(SRC_DIR)/c/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRS):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(ISO_DIR)

validate:
	grub-file --is-x86-multiboot $(KERNEL_BIN) || echo "Invalid multiboot header"

isodir: $(DIRS) $(KERNEL_BIN)	
	mv $(KERNEL_BIN) $(BOOT_DIR)/kernel.bin
	cp $(GRUBCONF) $(GRUB_DIR)/grub.cfg

start: kernel
	VBoxManage startvm Mine

.PHONY: $(LIBK) kernel