; Constantes Multiboot
MAGIC    equ 0x1BADB002
FLAGS    equ 0x03       ; ALIGN + MEMINFO
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384 ;
stack_top:

section .text
global _ultrakerneldefoulinustorvaldnaquabiensetenir
extern kmain

_ultrakerneldefoulinustorvaldnaquabiensetenir:
    mov esp, stack_top 
    call kmain
    cli          
.halt:
    hlt             
    jmp .halt
