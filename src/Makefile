CC      = i686-elf-gcc
AS      = nasm
LD      = i686-elf-ld

NAME    = kfs.bin
SRC_C   = kernel.c
SRC_S   = boot.s
OBJ     = $(SRC_C:.c=.o) $(SRC_S:.s=.o)
LINKER  = linker.ld

# flags obligatoire pour le mendatory
CFLAGS  = -m32 -ffreestanding -fno-builtin -fno-stack-protector \
          -nostdlib -nodefaultlibs -Wall -Wextra

ASFLAGS = -f elf32

# --- Règles ---

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking kernel..."
	$(LD) -m elf_i386 -T $(LINKER) -o $(NAME) $(OBJ)
	@echo "Kernel $(NAME) généré."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	@$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f kfs.iso

re: fclean all

iso: all
	@mkdir -p isodir/boot/grub
	@cp $(NAME) isodir/boot/
	@echo 'menuentry "kfs" { multiboot /boot/$(NAME) }' > isodir/boot/grub/grub.cfg #nommage kernel grub
	grub-mkrescue -o kfs.iso isodir
	@echo "ISO kfs.iso générée."

.PHONY: all clean fclean re iso
