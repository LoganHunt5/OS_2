ASM=nasm
SRC_DIR=src
BUILD_DIR=build
CC_PATH=/home/logan/opt/cross/bin
CC=$(CC_PATH)/i686-elf-gcc
ACC=$(CC_PATH)/i686-elf-as

run:
	rm -rf $(BUILD_DIR)/*
	rm -f kernel.iso
	rm -rf isodir
	$(ACC) $(SRC_DIR)/boot.s -o $(BUILD_DIR)/boot.o
	$(CC) -c $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel -ffreestanding -O2 -nostdlib $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o -lgcc
	mkdir -p isodir/boot/grub
	cp $(BUILD_DIR)/kernel isodir/boot/kernel
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir
	qemu-system-i386 -cdrom kernel.iso

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf isodir
	rm -f kernel.iso

test:
	qemu-system-i386 -s -S -fda $(BUILD_DIR)/floppy.img

debug:
	@echo "Current PATH is: $(PATH)"
	@which i686-elf-gcc || echo "Compiler not found in PATH"
