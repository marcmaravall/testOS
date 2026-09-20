CC=i686-elf-gcc
AS=i686-elf-as
QEMU=qemu-system-i386

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -MMD -MP -I.
ASFLAGS=
CPPASFLAGS=-ffreestanding -MMD -MP -I.
LDFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib

BUILD=build
ISO=$(BUILD)/os.iso
KERNEL=$(BUILD)/os

SRC_DIRS=.

find_src=$(patsubst ./%,%,$(shell find $(SRC_DIRS) -path ./$(BUILD) -prune -o -name '$(1)' -print))

C_SRCS=$(call find_src,*.c)
AS_SRCS=$(call find_src,*.s)
CPPAS_SRCS=$(call find_src,*.S)

C_OBJS=$(patsubst %.c,$(BUILD)/%.o,$(C_SRCS))
AS_OBJS=$(patsubst %.s,$(BUILD)/%.s.o,$(AS_SRCS))
CPPAS_OBJS=$(patsubst %.S,$(BUILD)/%.S.o,$(CPPAS_SRCS))

ASM_OBJS=$(AS_OBJS) $(CPPAS_OBJS)

BOOT_OBJ=$(BUILD)/boot.s.o
OBJS=$(filter $(BOOT_OBJ),$(ASM_OBJS)) $(filter-out $(BOOT_OBJ),$(ASM_OBJS)) $(C_OBJS)

DEPS=$(C_OBJS:.o=.d) $(CPPAS_OBJS:.o=.d)

ISO_DIR=$(BUILD)/isodir
BOOT_DIR=$(ISO_DIR)/boot
GRUB_DIR=$(BOOT_DIR)/grub

all: $(ISO)

$(BUILD)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(BUILD)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CPPASFLAGS) -c $< -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJS) linker.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgcc

$(ISO): $(KERNEL)
	mkdir -p $(GRUB_DIR)
	cp $(KERNEL) $(BOOT_DIR)/os
	printf 'menuentry "OS" {\n' > $(GRUB_DIR)/grub.cfg
	printf '    multiboot /boot/os\n' >> $(GRUB_DIR)/grub.cfg
	printf '    boot\n' >> $(GRUB_DIR)/grub.cfg
	printf '}\n' >> $(GRUB_DIR)/grub.cfg
	grub-mkrescue -o $(ISO) $(ISO_DIR)

run: $(ISO)
	$(QEMU) -cdrom $(ISO)

clean:
	rm -rf $(BUILD)

-include $(DEPS)

.PHONY: all run clean
