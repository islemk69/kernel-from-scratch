; Constantes Multiboot
MAGIC    equ 0x1BADB002
FLAGS    equ 0x03       ; ALIGN + MEMINFO
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

global gdt_flush
gdt_flush:
    mov eax, [esp + 4]  ; Récupère le pointeur vers gdt_p
    lgdt [eax]          ; Charge la GDT 
    
    ; On recharge les segments de données (0x10 est l'offset du Kernel Data)
    mov ax, 0x10      
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    ; Far jump pour recharger CS (le segment de code à l'offset 0x08)
    jmp 0x08:.flush_cs
.flush_cs:
    ret

section .bss
align 16
stack_bottom:
    resb 16384 ;
stack_top:

section .text
global _start
extern kmain

_start:
    mov esp, stack_top 
    call kmain
    cli          
.halt:
    hlt             
    jmp .halt
