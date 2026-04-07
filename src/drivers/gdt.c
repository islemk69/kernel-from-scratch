#include "gdt.h"

struct gdt_table *gdt_table = (struct gdt_table *)0x00000800;
struct gdt_ptr gdt_p;

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_table[num].base_low    = (base & 0xFFFF);
    gdt_table[num].base_middle = (base >> 16) & 0xFF;
    gdt_table[num].base_high   = (base >> 24) & 0xFF;

    gdt_table[num].limit_low   = (limit & 0xFFFF);
    gdt_table[num].granularity = (limit >> 16) & 0x0F;
    gdt_table[num].granularity |= gran & 0xF0;
    gdt_table[num].access      = access;
}

void init_gdt() {
    gdt_p.limit = (sizeof(struct gdt_table) * 7) - 1;
    gdt_p.base  = 0x00000800;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment 
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code 
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data 
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Stack 
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code 
    gdt_set_gate(5, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Data 
    gdt_set_gate(6, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Stack 

    // Appel assembleur
    gdt_flush((uint32_t)&gdt_p);
}