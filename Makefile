ASM=nasm
SRC_DIR=src
BUILD_DIR=build
CC_PATH=/home/logan/opt/cross/bin
CC=$(CC_PATH)/i686-elf-gcc
ACC=$(CC_PATH)/i686-elf-as

# Find all .c files
C_SOURCES = $(shell find $(SRC_DIR) -name '*.c')

# Convert src/path/file.c -> build/path/file.o
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

# Add the boot object
ALL_OBJECTS = $(OBJ) $(BUILD_DIR)/boot.o

run: kernel.iso
	qemu-system-i386 -serial stdio -cdrom kernel.iso

# Build the ISO
# Note: We now depend on kernel.bin, but we can copy it to isodir as just "kernel"
kernel.iso: $(BUILD_DIR)/kernel.bin
	mkdir -p isodir/boot/grub
	cp $(BUILD_DIR)/kernel.bin isodir/boot/kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir

# Linker Rule
# CHANGED: Output is now kernel.bin to avoid conflict with 'kernel' directory
$(BUILD_DIR)/kernel.bin: $(ALL_OBJECTS)
	$(CC) -T $(SRC_DIR)/boot/linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

# Compilation Rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Assembly Rule
$(BUILD_DIR)/boot.o: $(SRC_DIR)/boot/boot.s
	@mkdir -p $(BUILD_DIR)
	$(ACC) $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf isodir
	rm -f kernel.iso
