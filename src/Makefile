CC      = i686-elf-gcc
AS      = nasm
LD      = i686-elf-ld

NAME    = kfs.bin
SRC_C   = kernel.c
SRC_S   = boot.s
OBJ     = $(SRC_C:.c=.o) $(SRC_S:.s=.o)
LINKER  = linker.ld

# --- Flags obligatoires (Source: Sujet III.2.2) ---
# On ajoute -m32 pour forcer l'architecture i386 demandée 
CFLAGS  = -m32 -ffreestanding -fno-builtin -fno-stack-protector \
          -nostdlib -nodefaultlibs -Wall -Wextra [cite: 62, 63, 65, 67, 68]

ASFLAGS = -f elf32

# --- Règles ---

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking kernel..."
	$(LD) -m elf_i386 -T $(LINKER) -o $(NAME) $(OBJ) [cite: 73, 102]
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

# --- Règle Bonus : Génération de l'ISO (si grub-mkrescue est là) ---
iso: all
	@mkdir -p isodir/boot/grub
	@cp $(NAME) isodir/boot/
	@echo 'menuentry "kfs" { multiboot /boot/$(NAME) }' > isodir/boot/grub/grub.cfg
	grub-mkrescue -o kfs.iso isodir
	@echo "ISO kfs.iso générée."

.PHONY: all clean fclean re iso
