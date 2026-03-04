ENTRY(_ultrakerneldefoulinustorvaldnaquabiensetenir)

SECTIONS
{
    /* de 0 a 640ko = données sensible ou bride d'ancien code BIOS etc */
    /* entre les deux = mémoire VGA */
    /* 1mo = mémoire étendue endroit standard et ur pour comencer a écrre en 32bits. */
    . = 1M; 

    /* on s'assure que chaques sections commence au début d'une nouvelle page physique en RAM (4096octets)*/

    /* section code */
    .text : ALIGN(4K)
    {
        *(.multiboot) 
        *(.text)
    }

    /* section de constante (ex cont char c = 'a' / "kernel panic" etc) */
    .rodata : ALIGN(4K) 
    { 
        *(.rodata) 
    }

    /* section varaibles définies (ex: int i = 0) */
    .data   : ALIGN(4K) 
    { 
        *(.data)   
    }

    /* section varaibles non définies (ex: char *str[254]);*/
    .bss    : ALIGN(4K) 
    { 
        *(COMMON) *(.bss)  
    }
}